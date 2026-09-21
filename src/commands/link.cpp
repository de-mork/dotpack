#include "link.h"
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
