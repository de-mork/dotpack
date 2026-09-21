#include "commands/link.h"
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "usage: dotpack <command>\n";
        std::cerr << "commands: scan, link, update, push\n";
        return 2;
    }

    std::string command = argv[1];

    if (command == "scan") {
        std::cout << "TODO: scan\n";
        return 0;
    } else if (command == "link") {
        if (argc != 4) {
            std::cerr << "usage: dotpack link <src> <dst>\n";
            return 2;
        }
        fs::path src = argv[2];
        fs::path dst = argv[3];

        if (!link_one(src, dst))
            return 1;

        return 0;
    } else if (command == "update") {
        std::cout << "TODO: update\n";
        return 0;
    } else if (command == "push") {
        std::cout << "TODO: push\n";
        return 0;
    } else {
        std::cerr << "unknown command: " << command << "\n";
        return 3;
    }
}
