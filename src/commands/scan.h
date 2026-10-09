#pragma once
#include <filesystem>
#include <vector>

struct ScanRoot {
    std::filesystem::path path;
    bool recursive;
};

std::vector<std::filesystem::path>
scan_directories(const std::vector<ScanRoot> &roots);
int run_scan();
