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

LinkStatus get_link_status(const std::filesystem::path &src,
                           const std::filesystem::path &dst);

std::string trim(const std::string &line);
std::string expand_tilde(const std::string &line);

std::filesystem::path home_dir();
std::filesystem::path config_path();
std::filesystem::path dotfiles_dir();
