#include "config.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <string>

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
