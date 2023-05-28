/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Logger.cpp
*/

#include <iostream>
#include "Logger.hpp"

plazza::Logger::Logger(const std::string &filepath, const std::string &debugFilepath) {
    this->_log.open(filepath);
    this->_debug.open(debugFilepath);
    if (!this->_log.is_open() || !this->_debug.is_open()) {
        throw LoggerException();
    }
}

plazza::Logger::~Logger() {
    this->_log.close();
    this->_debug.close();
}

void plazza::Logger::operator<<(const std::string &message) {
    this->_log << message << std::endl;
    this->_debug << message << std::endl;
    std::cout << message << std::endl;
}

void plazza::Logger::operator>>(const std::string &message) {
    this->_debug << message << std::endl;
}
