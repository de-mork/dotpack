#pragma once
#include <filesystem>
#include <string>

std::string trim(const std::string &line);
std::string expand_tilde(const std::string &line);

std::filesystem::path home_dir();
std::filesystem::path config_path();
std::filesystem::path dotfiles_dir();
