/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Logger.cpp
*/

#include "Logger.hpp"

plazza::Logger::Logger(const std::string &_filepath) {
    this->_file.open(_filepath);
    if (!this->_file.is_open()) {
        throw LoggerException();
    }
}

plazza::Logger::~Logger() {
    this->_file.close();
}

void plazza::Logger::log(const std::string &message) {
    this->_file << message << std::endl;
}
