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

std::vector<std::string> read(std::istream& in) {
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line))
        lines.emplace_back(move(line));
    return lines;
}

const std::string INCLUDE = "#include \"";
const std::string IFNDEF = "#ifndef ";
const std::string DEFINE = "#define ";
const std::string ENDIF = "#endif";

std::vector<std::string> include_headers(const std::vector<std::string>& lines, std::set<std::string>& included) {
    std::vector<std::string> result;
    std::string header_guard = "";
    size_t last_endif = 0;
    for (const auto& line : lines) {
        bool add_line = true;
        if (auto pos = line.find(INCLUDE); pos != std::string::npos) {
            add_line = false;
            pos += INCLUDE.size();
            if (std::string header = line.substr(pos, line.find('"', pos) - pos); included.find(header) == included.end()) {
                included.insert(header);
                std::ifstream fin(header);
                auto res = include_headers(read(fin), included);
                result.insert(result.end(), res.begin(), res.end());
            }
        } else if (auto pos = line.find(IFNDEF); pos != std::string::npos) {
            pos += IFNDEF.size();
            if (std::string name = line.substr(pos, line.find(' ', pos) - pos); name.find("_HPP") == name.size() - 4) {
                add_line = false;
                header_guard = name;
            }
        } else if (!header_guard.empty()) {
            if (auto pos = line.find(DEFINE); pos != std::string::npos) {
                pos += DEFINE.size();
                if (std::string name = line.substr(pos, line.find(' ', pos) - pos); name == header_guard)
                    add_line = false;
            } else if (auto pos = line.find(ENDIF); pos != std::string::npos)
                last_endif = result.size();
        }
        if (add_line)
            result.emplace_back(line);
    }
    if (!header_guard.empty())
        result.erase(result.begin() + last_endif);
    return result;
}

int main() {
    std::set<std::string> included;
    auto result = include_headers(read(std::cin), included);
    for (const auto& line : result)
        std::cout << line << '\n';
}
