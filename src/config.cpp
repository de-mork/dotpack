#include "config.h"
#include "utils.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

std::vector<Entry> read_config(const std::filesystem::path &path) {
    std::vector<Entry> entries;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "error: cannot open config: " << path << "\n";
        return entries;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;

        auto pos = line.find("->");
        if (pos == std::string::npos) {
            std::cerr << "error: invalid line in config: " << line << "\n";
            continue;
        }

        std::string left = expand_tilde(trim(line.substr(0, pos)));
        std::string right = expand_tilde(trim(line.substr(pos + 2)));

        Entry e;
        e.system_path = left;
        e.repo_path = right;

        entries.push_back(e);
    }
    return entries;
}

WriteStatus write_config(const std::filesystem::path &system_path,
                         const std::filesystem::path &repo_path) {
    auto entries = read_config(config_path());
    for (const auto &e : entries) {
        if (e.system_path == system_path)
            return WriteStatus::AlreadyExists;
    }

    std::ofstream file(config_path(), std::ios::app);

    if (!file.is_open()) {
        std::cerr << "error: cannot open config: " << config_path() << "\n";
        return WriteStatus::Error;
    }

    file << std::left << std::setw(40) << to_tilde(system_path) << " -> "
         << to_tilde(repo_path) << "\n";
    return WriteStatus::Written;
}
