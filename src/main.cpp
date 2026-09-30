#include "commands/check.h"
#include "commands/link.h"
#include "commands/push.h"
#include "commands/scan.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "usage: dotpack <command>\n";
        std::cerr << "commands: link, check, push, scan, collect, setup\n";
        return 2;
    }

    std::string command = argv[1];

    if (command == "scan") {
        return run_scan();
    } else if (command == "link") {
        return run_link();
    } else if (command == "check") {
        return run_check();
    } else if (command == "push") {
        return run_push();
    } else {
        std::cerr << "unknown command: " << command << "\n";
        return 3;
    }
}
