#include "BobUtils.h"
#include "spdlog/spdlog.h"

#include <fstream>
#include <sstream>
#include <string>

namespace Bob {

std::string ReadFile(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        spdlog::error("Error opening the file: '{:s}'", path);
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

}; // namespace Bob
