#include "utils.h"
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <vector>

static const std::vector<std::string> whitelist_ext{
    ".conf", ".yaml", ".rasi", ".jsonc", ".toml", ".lua", ".json"};

static const std::vector<std::string> whitelist_names{"config", "zshrc",
                                                      "gitconfig", "bashrc"};

static const std::vector<std::string> blacklist_ext{
    ".log", ".tmp", ".pid", ".swp", ".swo", ".lock", ".bak", ".old", ".orig"};

static const std::vector<std::string> blacklist_names{".local",
                                                      ".cache",
                                                      "void-packages",
                                                      "zen",
                                                      ".var",
                                                      ".git",
                                                      ".mozilla",
                                                      "Applications",
                                                      "Logs",
                                                      "dotnet",
                                                      ".dotnet",
                                                      ".cargo",
                                                      "build",
                                                      "Projects",
                                                      ".cmake",
                                                      ".oh-my-zsh",
                                                      "platform-tools",
                                                      "AmneziaVPN",
                                                      ".steam",
                                                      "obs-studio",
                                                      "libreoffice",
                                                      "unity3d",
                                                      "AmneziaVPN.ORG",
                                                      "dotpack",
                                                      "dotfiles",
                                                      "lazy-lock.json",
                                                      "lazyvim.json",
                                                      "vesktop",
                                                      "OpenTabletDriver"};

std::string trim(const std::string &line) {
    bool first = true;
    size_t start = 0;
    size_t end = line.size() - 1;

    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] != ' ' && line[i] != '\t') {
            if (first) {
                start = i;
                first = false;
            }
            end = i;
        }
    }
    if (first)
        return "";
    return line.substr(start, end - start + 1);
}

std::string expand_tilde(const std::string &line) {
    if (!line.empty() && line[0] == '~') {
        const char *home = std::getenv("HOME");

        if (home == nullptr)
            return line;

        std::string edited_line = home + line.substr(1);
        return edited_line;
    }

    return line;
}

std::filesystem::path home_dir() {
    const char *home = std::getenv("HOME");
    if (home == nullptr)
        return std::filesystem::path();

    return std::filesystem::path(home);
}

std::filesystem::path config_path() {
    auto home = home_dir();
    if (home.empty())
        return {};

    return home / ".config" / "dotpack" / "config";
}

std::filesystem::path dotfiles_dir() {
    auto home = home_dir();
    if (home.empty())
        return {};

    return home / "dotfiles";
}

LinkStatus get_link_status(const std::filesystem::path &target,
                           const std::filesystem::path &link) {
    if (std::filesystem::is_symlink(link)) {
        if (std::filesystem::read_symlink(link) == target)
            return LinkStatus::Ok;
        if (std::filesystem::exists(link))
            return LinkStatus::WrongLink;
        return LinkStatus::Broken;
    }
    if (std::filesystem::exists(link))
        return LinkStatus::RealFile;
    return LinkStatus::Missing;
}

bool is_config_candidate(const std::filesystem::path &path) {
    if (std::filesystem::is_directory(path))
        return false;
    std::string name = path.filename().string();
    std::string ext = path.extension().string();

    if (!name.empty() && name[0] == '.')
        name = name.substr(1);

    bool ext_match = std::find(whitelist_ext.begin(), whitelist_ext.end(),
                               ext) != whitelist_ext.end();
    bool name_match = std::find(whitelist_names.begin(), whitelist_names.end(),
                                name) != whitelist_names.end();

    return ext_match || name_match;
}

bool should_skip(const std::filesystem::path &path) {
    std::string name = path.filename().string();
    std::string ext = path.extension().string();

    bool ext_match = std::find(blacklist_ext.begin(), blacklist_ext.end(),
                               ext) != blacklist_ext.end();
    bool name_match = std::find(blacklist_names.begin(), blacklist_names.end(),
                                name) != blacklist_names.end();

    return ext_match || name_match;
}
