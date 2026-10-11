#include "commands/check.h"
#include "commands/collect.h"
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
        if (argc > 2)
            return run_link(argv[2]);
        return run_link();
    } else if (command == "check") {
        return run_check();
    } else if (command == "push") {
        if (argc > 2)
            return run_push(argv[2]);
        return run_push();
    } else if (command == "collect") {
        if (argc > 2)
            return run_collect(argv[2]);
        return run_collect();
    } else {
        std::cerr << "unknown command: " << command << "\n";
        return 3;
    }
}
