#include <iostream>

// file reading stuff
#include "utils.hpp"
#include "debug.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <GLFW/glfw3.h>

std::string GetFile(const std::string &path) {
    std::string content;
    std::ifstream file(path);

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            content = buffer.str();
            file.close();
            LOG(std::string("File '") + path + "' successfully read");
        } else {
            std::cerr << "Unable to open file '" << path << "'" << std::endl;
        }
    } catch (std::ifstream::failure e) {
        std::cout << "[Reading Error] FILE_READ::FILE_NOT_SUCCESFULLY_READ L "
                     "BOZO HOW DID YOU FAIL THIS?"
                  << std::endl;
    }

    return content;
}

void glfwError(std::string msg) {
    std::cout << msg << std::endl;
    glfwTerminate();
}
