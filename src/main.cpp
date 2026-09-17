#include <filesystem>
#include <iostream>
#include <string>
namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  if (argc < 5) {
    std::cerr << "usage: dotpack dot link <src> <dst>\n";
    return 1;
  }

  std::string arg1 = argv[1];
  std::string arg2 = argv[2];

  if (arg1 != "dot" || arg2 != "link") {
    std::cerr << "unknown command\n";
    return 1;
  }

  fs::path src = argv[3];
  fs::path dst = argv[4];

  if (!fs::exists(src)) {
    std::cerr << "error: source not found: " << src << "\n";
    return 1;
  }

  if (fs::exists(dst)) {
    std::cerr << "error: exists\n";
    return 1;
  }

  try {
    fs::create_symlink(src, dst);
    std::cout << "linked " << src << " -> " << dst << "\n";
  } catch (const fs::filesystem_error &e) {
    std::cerr << "error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
