#include "check.h"
#include "config.h"
#include "utils.h"
#include <filesystem>
#include <iostream>

int run_check() {
    auto cfg = config_path();
    if (cfg.empty()) {
        std::cerr << "error: HOME not set\n";
        return 1;
    }

    auto entries = read_config(cfg);
    int problems = 0;

    for (const auto &entry : entries) {
        std::filesystem::path dst = entry.system_path;
        std::filesystem::path src = entry.repo_path;

        if (std::filesystem::is_symlink(dst)) {
            if (std::filesystem::read_symlink(dst) == src)
                std::cout << "OK          " << dst << "\n";
            else if (std::filesystem::exists(dst)) {
                std::cout << "WRONG_LINK  " << dst << "\n";
                problems++;
            } else {
                std::cout << "BROKEN      " << dst << "\n";
                problems++;
            }

        } else {
            if (std::filesystem::exists(dst)) {
                std::cout << "REAL_FILE   " << dst << "\n";
                problems++;
            } else {
                std::cout << "MISSING     " << dst << "\n";
                problems++;
            }
        }
    }
    return problems == 0 ? 0 : 1;
}
