#include "collect.h"
#include "config.h"
#include "scan.h"
#include "utils.h"
#include <filesystem>
#include <iostream>
#include <string>

std::filesystem::path compute_repo_path(const std::filesystem::path &path) {
    std::filesystem::path system_path =
        std::filesystem::relative(path, home_dir());

    std::string sys = system_path.string();
    if (sys.rfind(".config/", 0) == 0)
        sys = sys.substr(8);
    std::filesystem::path p(sys);

    std::string name = p.filename().string();
    if (!name.empty() && name[0] == '.') {
        name = name.substr(1);
        p = p.parent_path() / name;
    }

    return dotfiles_dir() / p;
}

int run_collect(std::string flag) {
    std::vector<ScanRoot> roots = {
        {home_dir() / ".config", true},
        {home_dir(), false},
    };

    auto candidates = scan_directories(roots);
    auto entries = read_config(config_path());

    for (const std::filesystem::path &path : candidates) {
        std::filesystem::path repo_path = compute_repo_path(path);

        bool already_in_config = false;
        for (const auto &e : entries) {
            if (e.system_path == path) {
                already_in_config = true;
                break;
            }
        }

        if (already_in_config && flag != "--all")
            continue;

        std::cout << path << ": add to dotfiles? [y/n] - ";
        std::string answer;
        std::getline(std::cin, answer);

        if (answer != "y" && answer != "Y")
            continue;

        try {
            std::filesystem::create_directories(repo_path.parent_path());
            std::filesystem::copy(
                path, repo_path,
                std::filesystem::copy_options::recursive |
                    std::filesystem::copy_options::overwrite_existing);
            switch (write_config(path, repo_path)) {
            case WriteStatus::Written:
                std::cout << "added: " << path << "\n";
                break;
            case WriteStatus::AlreadyExists:
                std::cout << "already in config: " << path << "\n";
                break;
            case WriteStatus::Error:
                std::cerr << "error: " << path << ": cannot write to config\n";
                break;
            }
        } catch (const std::filesystem::filesystem_error &e) {
            std::cerr << "error: " << e.what() << "\n";
        }
    }
    return 0;
}
