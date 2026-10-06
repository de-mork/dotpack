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

        LinkStatus status = get_link_status(src, dst);
        switch (status) {
        case LinkStatus::Ok:
            std::cout << "OK          " << dst << "\n";
            break;
        case LinkStatus::WrongLink:
            std::cout << "WRONG_LINK  " << dst << "\n";
            problems++;
            break;
        case LinkStatus::Broken:
            std::cout << "BROKEN      " << dst << "\n";
            problems++;
            break;
        case LinkStatus::RealFile:
            std::cout << "REAL_FILE   " << dst << "\n";
            problems++;
            break;
        case LinkStatus::Missing:
            std::cout << "MISSING     " << dst << "\n";
            problems++;
            break;
        }
    }
    return problems == 0 ? 0 : 1;
}
