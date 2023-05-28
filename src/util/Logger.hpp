/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Logger.hpp
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#define LOG_FILEPATH "plazza.log"
#define DEBUG_FILEPATH "plazza.debug.log"

#include <fstream>
#include <string>

namespace plazza {
    class LoggerException : public std::exception {

    };

    class Logger {
        public:
            explicit Logger(const std::string &filepath = LOG_FILEPATH, const std::string &debugFilepath = DEBUG_FILEPATH);
            ~Logger();

            void operator<<(const std::string &message);
            void operator>>(const std::string &message);

        private:
            std::ofstream _log;
            std::ofstream _debug;
    };
}

#endif
