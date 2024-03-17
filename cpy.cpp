#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>

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
    char e = argv[2][0] + 1;
    copy("0.cpp", dir + "0.cpp");
    copy("input.txt", dir + "input.txt");
    for (char c = 'A'; c < e; ++c)
        copy("0.cpp", dir + c + ".cpp");
    std::cout << std::max(e-'A',0) << " files created" << std::endl;
    return 0;
}
