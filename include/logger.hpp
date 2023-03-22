#pragma once
#include <cstdlib>
#include <string>
#include <iostream>
#include <concepts>

namespace sgl {

static const std::string __GREEN = "\x1B[32m";
static const std::string __RED = "\x1B[31m";
static const std::string __YELLOW = "\x1B[33m";
static const std::string __RESET = "\x1B[0m";


void log_info(std::string msg);
void log_warn(std::string msg);
void log_error(std::string msg);

} // namespace sgl
