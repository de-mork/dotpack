#include "link.h"
#include "config.h"
#include "utils.h"
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>

bool link_one(const std::filesystem::path &src,
              const std::filesystem::path &dst, std::string flag) {
    if (!std::filesystem::exists(src)) {
        std::cerr << "error: source not found: " << src << "\n";
        return false;
    }
    LinkStatus status = get_link_status(src, dst);
    switch (status) {
    case LinkStatus::Ok:
        std::cerr << "already linked: " << dst << "\n";
        return true;
    case LinkStatus::WrongLink:
        std::cerr << "error: wrong link: " << dst << "\n";
        return false;
    case LinkStatus::Broken:
        std::cerr << "error: broken symlink: " << dst << "\n";
        return false;
    case LinkStatus::RealFile:
        std::cerr << "error: destination already exists: " << dst << "\n";
        return false;
    case LinkStatus::Missing:
        try {
            std::filesystem::create_directories(dst.parent_path());
            std::filesystem::create_symlink(src, dst);
            std::cout << "linked " << src << " -> " << dst << "\n";
            return true;
        } catch (const std::filesystem::filesystem_error &e) {
            std::cerr << "error: " << e.what() << "\n";
            return false;
        }
    }
    return false;
}

int run_link(std::string flag) {
    std::filesystem::path cfg = config_path();
    if (cfg.empty()) {
        std::cerr << "error: HOME not set\n";
        return 1;
    }

    auto entries = read_config(cfg);

    int failures = 0;
    for (const auto &entry : entries) {
        std::filesystem::path src = entry.repo_path;
        std::filesystem::path dst = entry.system_path;

        if (!link_one(src, dst, flag))
            failures++;
    }

    return failures == 0 ? 0 : 1;
}
