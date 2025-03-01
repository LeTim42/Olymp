#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <windows.h>

const std::vector<std::string> FILES = {
    "main.cpp",
    "olymp/main.hpp",
    "olymp/other.hpp",
    "olymp/search.hpp",
    "olymp/mod.hpp",
    "olymp/dsu.hpp",
    "olymp/graph.hpp",
    "olymp/rnd.hpp",
    "olymp/geom.hpp",
    "olymp/strings.hpp",
    "olymp/bitset.hpp",
    "olymp/bigint.hpp",
    "olymp/rational.hpp",
    "olymp/sparsetable.hpp",
    "olymp/segtree.hpp",
    "input.txt"
};

void copy(std::string from, std::string to) {
    std::ifstream fin(from, std::ifstream::binary);
    if (!fin) {
        std::cout << "Failed to read file " << from << std::endl;
        exit(2);
    }
    fin.seekg(0, fin.end);
    long len = fin.tellg();
    fin.seekg(0, fin.beg);
    char *buffer = new char[len];
    fin.read(buffer, len);
    fin.close();
    std::ofstream fout(to, std::ofstream::binary);
    if (!fout) {
        std::cout << "Failed to write file " << to << std::endl;
        exit(3);
    }
    fout.write(buffer, len);
    fout.close();
    delete[] buffer;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }
    std::string dir = argv[1];
    CreateDirectory(argv[1], NULL);
    dir += "\\";
    CreateDirectory((dir + "olymp").c_str(), NULL);
    char e = argv[2][0] + 1;
    for (const std::string& file : FILES)
        copy(file, dir + file);
    for (char c = 'A'; c < e; ++c)
        copy(FILES[0], dir + c + ".cpp");
    std::cout << std::max(e-'A',0) << " files created" << std::endl;
    return 0;
}
