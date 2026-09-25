#pragma once
#include <filesystem>

bool link_one(const std::filesystem::path &src,
              const std::filesystem::path &dst);

int run_link();
