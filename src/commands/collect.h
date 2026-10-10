#pragma once
#include <filesystem>

std::filesystem::path compute_repo_path(const std::filesystem::path &path);
int run_collect();
