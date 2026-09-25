#include "commands/link.h"
#include <iostream>
#include <string>

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
        return run_link();
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
