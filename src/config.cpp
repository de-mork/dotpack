#include "config.h"
#include "utils.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

std::vector<Entry> read_config(const std::filesystem::path &path) {
    std::vector<Entry> entries;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "cannot open config " << path << "\n";
        return entries;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;

        auto pos = line.find("->");
        if (pos == std::string::npos) {
            std::cerr << "Error: Incorrect line in config: " << line << "\n";
            continue;
        }

        std::string left = trim(expand_tilde(line.substr(0, pos)));
        std::string right = trim(line.substr(pos + 2));

        Entry e;
        e.system_path = left;
        e.repo_name = right;

        entries.push_back(e);
    }
    return entries;
}
