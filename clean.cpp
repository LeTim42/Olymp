#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <regex>
#include <set>

#define PARENS ()
#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__
#define DEB(...) { __VA_OPT__(EXPAND(DEB_HELPER(__VA_ARGS__))) std::cout << std::endl; }
#define DEB_HELPER(var, ...) std::cout << ">> " << #var << " = " << (var) << " "; __VA_OPT__(DEB_HELPER_2 PARENS (__VA_ARGS__))
#define DEB_HELPER_2() DEB_HELPER

#define PARENS ()
#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__
#define DEB(...) { __VA_OPT__(EXPAND(DEB_HELPER(__VA_ARGS__))) std::cout << std::endl; }
#define DEB_HELPER(var, ...) std::cout << ">> " << #var << " = " << (var) << " "; __VA_OPT__(DEB_HELPER_2 PARENS (__VA_ARGS__))
#define DEB_HELPER_2() DEB_HELPER

bool is_letter(char c) {
    return c == '_' || std::isalpha(c);
}

bool is_letter_or_digit(char c) {
    return is_letter(c) || ('0' <= c && c <= '9');
}

struct token {
    std::string value;
    size_t line;
};

struct def {
    std::string name;
    size_t line;
    std::vector<std::string> words;
};

struct var {
    size_t line;
    std::vector<std::string> names, words;
};

struct func {
    std::string name;
    size_t start, end;
    std::vector<std::string> words;
};

struct space {
    char type;
    std::string name;
    size_t start, end;
    std::vector<std::string> words;
    std::vector<def> defines, typedefs, usings;
    std::vector<var> vars;
    std::vector<func> funcs;
    std::vector<space> spaces;
};

class CppCode {
private:
    std::vector<token> tokens;
    size_t i, start = 0;
    std::vector<std::string> words_buffer, vars_buffer;
    space global;

    void get_tokens(std::vector<std::string>& lines) {
        for (size_t line = 0; line < lines.size(); ++line) {
            bool is_word_or_number = false;
            bool screening = false;
            char end_char = 0;
            std::string value = "";
            for (char c : lines[line]) {
                if (end_char) {
                    if (screening)
                        screening = false;
                    else if (c == end_char)
                        end_char = 0;
                    else
                        screening = c == '\\';
                    continue;
                }
                if (is_letter_or_digit(c)) {
                    if (!is_word_or_number) {
                        is_word_or_number = true;
                        value = "";
                    }
                    value += c;
                } else if (c == '\'' || c == '"')
                    end_char = c;
                else {
                    if (is_word_or_number) {
                        tokens.emplace_back(token{value, line});
                        is_word_or_number = false;
                    }
                    if (!std::isblank(c)) {
                        value = c;
                        tokens.emplace_back(token{value, line});
                    }
                }
            }
            if (is_word_or_number)
                tokens.emplace_back(token{value, line});
        }
    }

    void skip() {
        size_t line = tokens[i].line;
        while (i < tokens.size() && tokens[i].line == line) ++i;
        --i;
    }

    void ret() {
        size_t line = tokens[i].line;
        while (i != SIZE_MAX && tokens[i].line == line) --i;
        ++i;
    }

    template<class T>
    void unq(std::vector<T>& v) {
        std::sort(v.begin(), v.end());
        v.resize(std::unique(v.begin(), v.end()) - v.begin());
    }

    def get_def() {
        ++i;
        def d{tokens[i].value, tokens[i].line};
        size_t line = tokens[i].line;
        for (++i; tokens[i].line == line; ++i)
            if (is_letter(tokens[i].value[0]))
                d.words.emplace_back(tokens[i].value);
        --i;
        return d;
    }

    func get_func() {
        func f{tokens[i-1].value, start};
        if (!is_letter(f.name[0])) used.insert(f.name);
        start = SIZE_MAX;
        if (f.start == SIZE_MAX) f.start = tokens[i].line;
        words_buffer.clear();
        vars_buffer.clear();
        ret();
        while (tokens[i].value != "{" && tokens[i].value != ";") {
            if (is_letter(tokens[i].value[0]))
                f.words.emplace_back(tokens[i].value);
            ++i;
        }
        if (tokens[i].value == "{") {
            size_t count = 1;
            for (++i; count; ++i) {
                if (tokens[i].value == "{")
                    ++count;
                else if (tokens[i].value == "}")
                    --count;
                else if (tokens[i].value == "#" || (tokens[i].value == "/" && tokens[i+1].value == "/"))
                    skip();
                else if (is_letter(tokens[i].value[0]))
                    f.words.emplace_back(tokens[i].value);
            }
            --i;
        }
        f.end = tokens[i].line;
        unq(f.words);
        return f;
    }

    space get_space(char type = 0) {
        i += type == 1;
        space s{type, tokens[i+1].value, start};
        start = SIZE_MAX;
        words_buffer.clear();
        vars_buffer.clear();
        if (s.start == SIZE_MAX) s.start = tokens[i].line;
        if (type == 0 || type == 3) while (tokens[i].value != "{" && tokens[i].value != ";") ++i;
        else if (type == 1) ++i;
        if (type == 3) {
            for (++i; i < tokens.size() && tokens[i].value != "}"; ++i)
                if (is_letter(tokens[i].value[0]))
                    s.words.emplace_back(tokens[i].value);
            s.end = tokens[i].line;
            return s;
        }
        if (type != 0 || tokens[i].value == "{") {
            size_t count = 1, brackets = 0;
            bool eq = false;
            for (i += type != 2; count && i < tokens.size(); ++i) {
                if (i && tokens[i-1].line != tokens[i].line) {
                    if (vars_buffer.empty())
                        s.words.insert(s.words.end(), words_buffer.begin(), words_buffer.end());
                    else {
                        s.vars.emplace_back(var{tokens[i-1].line, vars_buffer, words_buffer});
                        vars_buffer.clear();
                    }
                    words_buffer.clear();
                    eq = false;
                }
                std::string value = tokens[i].value;
                if (value == (type == 0 ? "{" : (type == 1 ? "ifdef" : "")))
                    ++count;
                else if (value == (type == 0 ? "}" : (type == 1 ? "endif" : "")))
                    --count;
                else if (value == "#") {
                    if (tokens[i+1].line == tokens[i].line) {
                        bool define = tokens[i+1].value == "define";
                        bool undef = tokens[i+1].value == "undef";
                        if (define || undef) {
                            ++i;
                            size_t tmp = i;
                            def d = get_def();
                            if (d.name == "DONT_CLEAN" && define) {
                                space ss;
                                for (; tokens[i].value != "undef" || tokens[i+1].value != d.name; ++i)
                                    if (is_letter(tokens[i].value[0]))
                                        ss.words.emplace_back(tokens[i].value);
                                ss.name = d.name;
                                ss.start = d.line;
                                ss.end = tokens[i].line;
                                ss.type = 1;
                                s.spaces.emplace_back(ss);
                                used.insert(d.name);
                                get_def();
                                continue;
                            }
                            if (i == tmp+1) used.insert(d.name);
                            s.defines.emplace_back(d);
                        } else if (tokens[i+1].value == "ifdef")
                            s.spaces.emplace_back(get_space(1));
                        else if (tokens[i+1].value == "else") {
                            if (type == 1) break;
                            --i;
                            space ss = get_space(1);
                            ss.name = "/" + s.spaces.back().name;
                            ++s.spaces.back().end;
                            s.spaces.emplace_back(ss);
                        } else if (type != 1 || tokens[i+1].value != "endif")
                            skip();
                    }
                } else if (value == "typedef") {
                    def d = get_def();
                    d.words.insert(d.words.begin(), d.name);
                    d.name = d.words.back();
                    d.words.pop_back();
                    s.typedefs.emplace_back(d);
                } else if (value == "using") {
                    def d = get_def();
                    if (d.name == "namespace") {
                        d.name = d.words[0];
                        d.words.clear();
                        used.insert(d.name);
                    }
                    s.usings.emplace_back(d);
                } else {
                    if (value == "template") {
                        start = std::min(start, tokens[i].line);
                        size_t count = 1;
                        for (i+=2; count; ++i) {
                            if (tokens[i].value == "<")
                                ++count;
                            else if (tokens[i].value == ">")
                                --count;
                        }
                    }
                    value = tokens[i].value;
                    if (value == "/") {
                        if (tokens[i+1].value == "/") {
                            if (i+2 < tokens.size() && tokens[i+2].value == "/") {
                                std::string comment = "///";
                                size_t line = tokens[i].line;
                                for (i += 3; i < tokens.size() && tokens[i].line == line; ++i)
                                    if (is_letter(tokens[i].value[0]))
                                        comment += " " + tokens[i].value;
                                --i;
                                s.spaces.emplace_back(space{0, comment, line, line});
                            } else {
                                start = std::min(start, tokens[i].line);
                                skip();
                            }
                        } else if (tokens[i+1].value == "*") {
                            start = std::min(start, tokens[i].line);
                            i += 3;
                            while (i < tokens.size() && !(tokens[i-1].value == "*" && tokens[i].value == "/")) ++i;
                        }
                    }
                    else if (value == "using") {
                        def d = get_def();
                        s.usings.emplace_back(d);
                        start = SIZE_MAX;
                    }
                    else if (value == "namespace" || value == "struct" || value == "class" || value == "enum")
                        s.spaces.emplace_back(get_space(value == "enum" ? 3 : 0));
                    else if (value == "(" && !eq && !brackets)
                        s.funcs.emplace_back(get_func());
                    else if (value == "," || value == ";" || value == "=") {
                        if (!eq && !words_buffer.empty()) {
                            vars_buffer.emplace_back(words_buffer.back());
                            words_buffer.pop_back();
                        }
                        std::string S = "=!+-*/%";
                        if (value == "=" && find(S.begin(), S.end(), tokens[i-1].value[0]) == S.end()) eq = true;
                        else if (value == "," && !brackets) eq = false;
                        else if (value == ";") brackets = 0;
                    } else if (value == "{")
                        brackets++;
                    else if (value == "}")
                        brackets--;
                    else if (is_letter(value[0]))
                        words_buffer.emplace_back(value);
                }
            }
            --i;
        }
        s.end = tokens[i].line;
        unq(s.words);
        return s;
    }

    void unq_space(space& s) {
        unq(s.words);
        for (def& d : s.defines) unq(d.words);
        for (def& d : s.typedefs) unq(d.words);
        for (def& d : s.usings) unq(d.words);
        for (var& v : s.vars) unq(v.words);
        for (func& f : s.funcs) unq(f.words);
        for (space& ss : s.spaces) unq_space(ss);
    }
public:
    CppCode(std::vector<std::string>& lines) {
        get_tokens(lines);
        start = SIZE_MAX;
        i = 0;
        global = get_space(2);
        global.name = "main";
        unq_space(global);
    }
private:
    void print_words(std::vector<std::string>& words) {
        if (words.size()) {
            std::cout << ':';
            for (auto w : words)
                std::cout << ' ' << w;
        }
        std::cout << std::endl;
    }

    void print_defs(std::vector<def>& defs, std::string name, std::string tab) {
        if (defs.size()) {
            std::cout << tab << "> " << name << std::endl;
            for (def& d : defs) {
                std::cout << tab << "  " << d.name << " [" << d.line+1 << "]";
                print_words(d.words);
            }
        }
    }

    void print_vars(std::vector<var>& vars, std::string tab) {
        if (vars.size()) {
            std::cout << tab << "> VARIABLES" << std::endl;
            for (var& v : vars) {
                std::cout << tab << ' ';
                for (auto w : v.names)
                    std::cout << ' ' << w;
                std::cout << " [" << v.line+1 << "]";
                print_words(v.words);
            }
        }
    }

    void print_funcs(std::vector<func>& funcs, std::string tab) {
        if (funcs.size()) {
            std::cout << tab << "> FUNCTIONS" << std::endl;
            for (func& f : funcs) {
                std::cout << tab << "  " << f.name << " [" << f.start+1 << "; " << f.end+1 << "]";
                print_words(f.words);
            }
        }
    }

    void print_spaces(std::vector<space>& spaces, std::string tab) {
        if (spaces.size()) {
            std::cout << tab << "> SPACES" << std::endl;
            for (space& s : spaces)
                print_space(s, tab + "  ");
        }
    }

    void print_space(space& s, std::string tab) {
        std::cout << tab << s.name << " [" << s.start+1 << "; " << s.end+1 << "]";
        print_words(s.words);
        print_defs(s.defines, "DEFINES", tab);
        print_defs(s.typedefs, "TYPEDEFS", tab);
        print_defs(s.usings, "USINGS", tab);
        print_vars(s.vars, tab);
        print_funcs(s.funcs, tab);
        print_spaces(s.spaces, tab);
    }
public:
    void print() {
        print_space(global, "");
    }
private:
    std::vector<size_t> unused;
    std::set<std::string> used;

    void add_used_words(std::vector<std::string>& words) {
        for (auto word : words)
            used.insert(word);
    }

    void add_used_defs(std::vector<def>& defs) {
        for (def& d : defs)
            if (used.find(d.name) != used.end())
                add_used_words(d.words);
    }

    void add_used_vars(std::vector<var>& vars) {
        for (var& v : vars)
            for (auto w : v.names)
                if (used.find(w) != used.end()) {
                    add_used_words(v.words); break;
                }
    }

    void add_used_funcs(std::vector<func>& funcs) {
        for (func& f : funcs)
            if (used.find(f.name) != used.end())
                add_used_words(f.words);
    }

    void add_used_space(space& s) {
        if (used.find(s.name) != used.end()) {
            add_used_words(s.words);
            add_used_defs(s.defines);
            add_used_defs(s.typedefs);
            add_used_defs(s.usings);
            add_used_vars(s.vars);
            add_used_funcs(s.funcs);
            add_used_spaces(s.spaces);
        }
    }

    void add_used_spaces(std::vector<space>& spaces) {
        for (space& s : spaces)
            add_used_space(s);
    }

    void add_unused_defs(std::vector<def>& defs) {
        for (def& d : defs)
            if (used.find(d.name) == used.end())
                unused.emplace_back(d.line);
    }

    void add_unused_vars(std::vector<var>& vars) {
        for (var& v : vars) {
            bool found = false;
            for (auto w : v.names)
                if (used.find(w) != used.end()) {
                    found = true; break;
                }
            if (!found)
                unused.emplace_back(v.line);
        }
    }

    void add_unused_funcs(std::vector<func>& funcs) {
        for (func& f : funcs)
            if (is_letter(f.name[0]) && used.find(f.name) == used.end())
                for (size_t i = f.start; i <= f.end; ++i)
                    unused.emplace_back(i);
    }

    void add_unused_space(space& s) {
        if (used.find(s.name) == used.end() && (s.name[0] != '/' || used.find(s.name.substr(1)) != used.end()))
            for (size_t i = s.start; i <= s.end; ++i)
                unused.emplace_back(i);
        else {
            if (s.type == 1) {
                unused.emplace_back(s.start);
                unused.emplace_back(s.end);
            }
            add_unused_defs(s.defines);
            add_unused_defs(s.typedefs);
            add_unused_defs(s.usings);
            add_unused_vars(s.vars);
            add_unused_funcs(s.funcs);
            add_unused_spaces(s.spaces);
        }
    }

    void add_unused_spaces(std::vector<space>& spaces) {
        for (space& s : spaces)
            add_unused_space(s);
    }
public:
    std::vector<size_t> get_unused_code() {
        used.insert("main");
        size_t size;
        do {
            size = used.size();
            add_used_space(global);
        } while (used.size() != size);
        add_unused_space(global);
        unq(unused);
        return unused;
    }
};

bool is_empty(const std::string& line) {
    return std::all_of(line.begin(), line.end(), isspace);
}

bool is_close_bracket(const std::string& line) {
    auto close_bracket = line.find('}');
    if (close_bracket == std::string::npos)
        return false;
    std::string s = line;
    s[close_bracket] = ' ';
    return is_empty(s);
}

bool is_empty(const std::string& line) {
    return std::all_of(line.begin(), line.end(), isspace);
}

bool is_close_bracket(const std::string& line) {
    auto close_bracket = line.find('}');
    if (close_bracket == std::string::npos)
        return false;
    std::string s = line;
    s[close_bracket] = ' ';
    return is_empty(s);
}

std::string clean(std::vector<std::string>& lines, std::vector<size_t>& unused) {
    std::vector<std::string> res;
    size_t j = 0;
    bool was_empty = true;
    for (size_t i = 0; i < lines.size(); ++i) {
        if (j < unused.size() && unused[j] == i) ++j;
        else if (bool empty = is_empty(lines[i]); !empty || !was_empty) {
            res.emplace_back(move(lines[i]));
            was_empty = empty;
        }
    }
    for (size_t i = 1; i < res.size() - 1; ++i)
        if (is_close_bracket(res[i - 1]) && is_empty(res[i]) && is_close_bracket(res[i + 1]))
            res.erase(res.begin() + i);
    std::string str = "";
    for (const std::string& line : res)
        str += line + "\n";
    return str;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(std::cin, line))
        lines.emplace_back(move(line));
    CppCode code(lines);
    bool log = !strcmp(argv[argc-1], "LOG");
    if (log) code.print();
    auto unused = code.get_unused_code();
    auto result = clean(lines, unused);
    std::cout << result;
}
