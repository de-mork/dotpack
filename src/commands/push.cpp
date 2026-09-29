#include "push.h"
#include "utils.h"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

int run_push() {
    auto dotfiles = dotfiles_dir();
    if (dotfiles.empty()) {
        std::cerr << "error: HOME not set\n";
        return 1;
    }

    if (!std::filesystem::exists(dotfiles / ".git")) {
        std::cerr << "error: " << dotfiles << " is not a git repo\n";
        return 1;
    }

    std::string dotfiles_path = dotfiles.string();

    std::string add_command = "git -C " + dotfiles_path + " add .";
    std::string commit_command =
        "git -C " + dotfiles_path + " commit -m 'dotpack: auto-commit'";
    std::string push_command = "git -C " + dotfiles_path + " push";

    if (std::system(add_command.c_str()) != 0) {
        std::cerr << "error: git add failed\n";
        return 1;
    }

    if (std::system(commit_command.c_str()) != 0) {
        std::cerr << "error: git commit failed\n";
        return 1;
    }

    if (std::system(push_command.c_str()) != 0) {
        std::cerr << "error: git push failed\n";
        return 1;
    }

    return 0;
}
