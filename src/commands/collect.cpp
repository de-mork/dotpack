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

int run_collect() {
    std::vector<ScanRoot> roots = {
        {home_dir() / ".config", true},
        {home_dir(), false},
    };

    auto candidates = scan_directories(roots);

    for (const std::filesystem::path &path : candidates) {
        std::cout << path << ": add to dotfiles? [y/n] - ";
        std::string answer;
        std::getline(std::cin, answer);
        if (answer != "y" && answer != "Y")
            continue;

        std::filesystem::path repo_path = compute_repo_path(path);

        try {
            std::filesystem::create_directories(repo_path.parent_path());
            std::filesystem::copy(
                path, repo_path,
                std::filesystem::copy_options::recursive |
                    std::filesystem::copy_options::overwrite_existing);
            if (write_config(path, repo_path))
                std::cout << "added: " << path << " -> " << repo_path << "\n";
            else
                std::cerr << "error: " << repo_path
                          << ": not added to config\n";
        } catch (const std::filesystem::filesystem_error &e) {
            std::cerr << "error: " << e.what() << "\n";
            continue;
        }
    }
    return 0;
}
