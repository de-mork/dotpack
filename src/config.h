#pragma once
#include <filesystem>
#include <vector>

struct Entry {
    std::filesystem::path system_path;
    std::filesystem::path repo_path;
};
enum class WriteStatus {
    Written,       // записали
    AlreadyExists, // уже было
    Error,         // не открылся файл
};

WriteStatus write_config(const std::filesystem::path &system_path,
                         const std::filesystem::path &repo_path);
std::vector<Entry> read_config(const std::filesystem::path &path);
