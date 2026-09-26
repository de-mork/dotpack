#include "commands/link.h"
#include "commands/push.h"
#include "commands/scan.h"
#include "commands/update.h"
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
        return run_scan();
    } else if (command == "link") {
        return run_link();
    } else if (command == "update") {
        return run_update();
    } else if (command == "push") {
        return run_push();
    } else {
        std::cerr << "unknown command: " << command << "\n";
        return 3;
    }
}
