#include "utils.h"
#include <cstdlib>

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
