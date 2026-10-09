#pragma once
#include <filesystem>
#include <string>

enum class LinkStatus {
    Ok,        // симлинк на src
    Missing,   // dst не существует
    WrongLink, // симлинк на другое
    Broken,    // битый симлинк
    RealFile,  // реальный файл
};

std::string trim(const std::string &line);
std::string expand_tilde(const std::string &line);

std::filesystem::path home_dir();
std::filesystem::path config_path();
std::filesystem::path dotfiles_dir();

LinkStatus get_link_status(const std::filesystem::path &src,
                           const std::filesystem::path &dst);

bool is_config_candidate(const std::filesystem::path &path);
bool should_skip(const std::filesystem::path &path);
