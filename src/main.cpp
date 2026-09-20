#include <filesystem>
#include <iostream>
#include <string>
namespace fs = std::filesystem;

bool link_one(const fs::path &src, const fs::path &dst) {
  if (!fs::exists(src)) {
    std::cerr << "error: source not found: " << src << "\n";
    return false;
  }

  if (fs::exists(dst)) {
    std::cerr << "error: destination already exists\n";
    return false;
  }

  try {
    fs::create_symlink(src, dst);
    std::cout << "linked " << src << " -> " << dst << "\n";
    return true;
  } catch (const fs::filesystem_error &e) {
    std::cerr << "error: " << e.what() << "\n";
    return false;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 5) {
    std::cerr << "usage: dotpack dot link <src> <dst>\n";
    return 1;
  }

  std::string command = argv[1];
  std::string subcommand = argv[2];

  if (command != "dot" || subcommand != "link") {
    std::cerr << "unknown command\n";
    return 1;
  }

  fs::path src = argv[3];
  fs::path dst = argv[4];

  if (!link_one(src, dst))
    return 1;

  return 0;
}
