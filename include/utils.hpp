#pragma once

#include <string>

/// Get the content of a file
std::string GetFile(const std::string &path);

/// Custom error function thingy... dont you worry about it
void glfwError(std::string msg);

/// Takes a symbolic type constant and returns its size
/// Probably missing a few types but those were the most important
unsigned long get_gl_type_size(unsigned int type);

void EngineError(const std::string &error_msg);
