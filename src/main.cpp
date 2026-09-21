#include "commands/link.h"
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  if (argc < 5) {
    std::cerr << "usage: dotpack dot link <src> <dst>\n";
    return 2;
  }

  std::string command = argv[1];
  std::string subcommand = argv[2];

  if (command != "dot" || subcommand != "link") {
    std::cerr << "unknown command\n";
    return 3;
  }

  fs::path src = argv[3];
  fs::path dst = argv[4];

  if (!link_one(src, dst))
    return 1;

  return 0;
}
