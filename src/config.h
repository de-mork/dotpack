#pragma once
#include <filesystem>
#include <string>
#include <vector>

struct Entry {
    std::filesystem::path system_path;
    std::string repo_name;
};

std::vector<Entry> read_config(const std::filesystem::path &path);
