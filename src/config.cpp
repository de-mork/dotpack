#include "config.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

std::string trim(const std::string &line) {
    bool first = true;
    size_t start = 0;
    size_t end = line.size() - 1;

    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] != ' ' && line[i] != '\t') {
            if (first) {
                start = i;
                first = false;
            }
            end = i;
        }
    }
    if (first)
        return "";
    return line.substr(start, end - start + 1);
}

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

        std::string left = trim(line.substr(0, pos));
        if (!left.empty() && left[0] == '~') {
            std::string home = std::getenv("HOME");
            left = home + left.substr(1);
        }
        std::string right = trim(line.substr(pos + 2));

        Entry e;
        e.system_path = left;
        e.repo_name = right;

        entries.push_back(e);
    }
    return entries;
}
