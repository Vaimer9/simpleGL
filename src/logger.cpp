#include <concepts>
#include <logger.hpp>
#include <iostream>
#include <fstream>

namespace sgl {

void log_info(std::string msg)
{
    std::cout << __GREEN << "[ INFO ] " << msg << __RESET << std::endl;
}

void log_warn(std::string msg)
{
    std::cout << __YELLOW << "[ WARN ] " << msg << __RESET << std::endl;
}

void log_error(std::string msg)
{
    std::cout << __RED << "[ ERROR] " << msg << __RESET << std::endl;
}

} // namespace sgl
