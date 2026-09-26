#include "link.h"
#include "config.h"
#include <cstdlib>
#include <iostream>

bool link_one(const std::filesystem::path &src,
              const std::filesystem::path &dst) {
    if (!std::filesystem::exists(src)) {
        std::cerr << "error: source not found: " << src << "\n";
        return false;
    }

    if (std::filesystem::exists(dst)) {
        std::cerr << "error: destination already exists\n";
        return false;
    }

    try {
        std::filesystem::create_symlink(src, dst);
        std::cout << "linked " << src << " -> " << dst << "\n";
        return true;
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "error: " << e.what() << "\n";
        return false;
    }
}

int run_link() {
    const char *home = std::getenv("HOME");
    if (home == nullptr) {
        std::cerr << "error: HOME not set\n";
        return 1;
    }

    std::filesystem::path config_path =
        std::filesystem::path(home) / ".config" / "dotpack" / "config";

    auto entries = read_config(config_path);

    int failures = 0;
    for (const auto &entry : entries) {
        std::filesystem::path src =
            std::filesystem::path(home) / "dotfiles" / entry.repo_name;
        std::filesystem::path dst = entry.system_path;

        if (!link_one(src, dst))
            failures++;
    }

    return failures == 0 ? 0 : 1;
}
