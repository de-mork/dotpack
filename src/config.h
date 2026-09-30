#pragma once
#include <filesystem>
#include <vector>

struct Entry {
    std::filesystem::path system_path;
    std::filesystem::path repo_path;
};

std::vector<Entry> read_config(const std::filesystem::path &path);
