#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <regex>
#include <set>
#include <sys/stat.h>
#include <windows.h>

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
                    if (c == end_char && !screening)
                        end_char = 0;
                    else screening = c == '\\';
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
        f.words.pop_back();
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
        space s{tokens[i+1].value, start};
        start = SIZE_MAX;
        words_buffer.clear();
        vars_buffer.clear();
        if (s.start == SIZE_MAX) s.start = tokens[i].line;
        if (type == 0) while (tokens[i].value != "{" && tokens[i].value != ";") ++i;
        else if (type == 1) ++i;
        if (type != 0 || tokens[i].value == "{") {
            size_t count = 1;
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
                        if (tokens[i+1].value == "define") {
                            ++i;
                            def d = get_def();
                            if (d.words.empty()) used.insert(d.name);
                            s.defines.emplace_back(d);
                        } else if (tokens[i+1].value == "ifdef")
                            s.spaces.emplace_back(get_space(1));
                        else if (type != 1 || tokens[i+1].value != "endif")
                            skip();
                    }
                } else if (value == "typedef") {
                    def d = get_def();
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
                            start = std::min(start, tokens[i].line);
                            skip();
                        } else if (tokens[i+1].value == "*") {
                            start = std::min(start, tokens[i].line);
                            i += 3;
                            while (i < tokens.size() && tokens[i-1].value == "*" && tokens[i].value == "/") ++i;
                        }
                    }
                    else if (value == "namespace" || value == "struct" || value == "class")
                        s.spaces.emplace_back(get_space());
                    else if (value == "(")
                        s.funcs.emplace_back(get_func());
                    else if (value == "," || value == ";" || value == "=") {
                        if (!eq && words_buffer.size()) {
                            vars_buffer.emplace_back(words_buffer.back());
                            words_buffer.pop_back();
                        }
                        if (value == "=") eq = true;
                        else if (value == ",") eq = false;
                    } else if (is_letter(value[0]))
                        words_buffer.emplace_back(value);
                }
            }
            --i;
        }
        s.end = tokens[i].line;
        unq(s.words);
        return s;
    }
public:
    CppCode(std::vector<std::string>& lines) {
        get_tokens(lines);
        start = SIZE_MAX;
        i = 0;
        global = get_space(2);
        global.name = "main";
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
            std::cout << tab << ' ' << name << std::endl;
            for (def& d : defs) {
                std::cout << tab << "  " << d.name << " [" << d.line+1 << "]";
                print_words(d.words);
            }
        }
    }

    void print_vars(std::vector<var>& vars, std::string tab) {
        if (vars.size()) {
            std::cout << tab << " VARIABLES" << std::endl;
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
            std::cout << tab << " FUNCTIONS" << std::endl;
            for (func& f : funcs) {
                std::cout << tab << "  " << f.name << " [" << f.start+1 << "; " << f.end+1 << "]";
                print_words(f.words);
            }
        }
    }

    void print_spaces(std::vector<space>& spaces, std::string tab) {
        if (spaces.size()) {
            std::cout << tab << " SPACES" << std::endl;
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
                    add_used_words(v.words);  break;
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
        if (used.find(s.name) == used.end())
            for (size_t i = s.start; i <= s.end; ++i)
                unused.emplace_back(i);
        else {
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

std::vector<std::string> read(std::string file) {
    std::ifstream fin(file);
    if (!fin) {
        std::cout << "Failed to open file " << file << std::endl;
        exit(2);
    }
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(fin, line))
        lines.emplace_back(line);
    fin.close();
    return lines;
}

void write(std::string file, std::string str) {
    std::ofstream fout(file);
    if (!fout) {
        std::cout << "Failed to open output file" << std::endl;
        exit(3);
    }
    fout << str;
    fout.close();
}

void copy(std::string str) {
    auto glob = GlobalAlloc(GMEM_FIXED, str.size()+1);
    memcpy(glob, str.c_str(), str.size()+1);
    OpenClipboard(GetDesktopWindow());
    EmptyClipboard();
    SetClipboardData(CF_TEXT,glob);
    CloseClipboard();
}

std::string clean(std::vector<std::string>& lines, std::vector<size_t>& unused) {
    std::string str = "";
    size_t j = 0;
    bool empty = true;
    for (size_t i = 0; i < lines.size(); ++i) {
        if (j < unused.size() && unused[j] == i) ++j;
        else if (lines[i].size() || !empty) {
            str += lines[i] + "\n";
            empty = !lines[i].size();
        }
    }
    return str;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No arguments" << std::endl;
        return 1;
    }
    std::string input = argv[1];
    if (input.find('.') == -1) input += ".cpp";
    auto lines = read(input);
    CppCode code(lines);
    // code.print();
    auto unused = code.get_unused_code();
    auto str = clean(lines, unused);
    if (argc < 3) copy(str);
    else {
        std::string output = argv[2];
        if (output.find('.') == -1) output += ".cpp";
        write(output, str);
    }
}
