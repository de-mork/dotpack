#include "scan.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
namespace fs = std::filesystem;

std::vector<fs::path> scan_directories(const std::vector<ScanRoot> &roots) {
    std::vector<fs::path> results;

    for (const auto &root : roots) {
        if (!fs::exists(root.path))
            continue;

        if (root.recursive) {
            for (auto it = fs::recursive_directory_iterator(root.path);
                 it != fs::recursive_directory_iterator(); ++it) {

                if (should_skip(it->path())) {
                    it.disable_recursion_pending();
                    continue;
                }
                if (is_config_candidate(it->path()))
                    results.push_back(it->path());
            }
        } else {
            for (auto &entry : fs::directory_iterator(root.path)) {
                if (!should_skip(entry.path()) &&
                    is_config_candidate(entry.path()))
                    results.push_back(entry.path());
            }
        }
    }

    std::sort(results.begin(), results.end());
    results.erase(std::unique(results.begin(), results.end()), results.end());
    return results;
}

int run_scan() {
    std::vector<ScanRoot> roots = {
        {home_dir() / ".config", true},
        {home_dir(), false},
    };

    auto results = scan_directories(roots);
    for (const auto &p : results) {
        std::cout << p << "\n";
    }
    return 0;
}
