#pragma once
#include <filesystem>
#include <string>

bool link_one(const std::filesystem::path &src,
              const std::filesystem::path &dst, std::string flag);

int run_link(std::string flag = "");
