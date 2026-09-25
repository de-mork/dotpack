#include "commands/link.h"
#include "config.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

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
        const char *home = std::getenv("HOME");

        fs::path config_path =
            fs::path(home) / ".config" / "dotpack" / "config";

        auto entries = read_config(config_path);

        int failures = 0;
        for (const auto &entry : entries) {
            fs::path src = fs::path(home) / "dotfiles" / entry.repo_name;
            fs::path dst = entry.system_path;

            if (!link_one(src, dst))
                failures++;
        }

        return failures == 0 ? 0 : 1;
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
