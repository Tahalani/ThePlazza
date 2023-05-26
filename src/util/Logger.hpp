/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Logger.hpp
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#define LOG_FILEPATH "plazza.log"

#include <fstream>
#include <string>

namespace plazza {
    class LoggerException : public std::exception {

    };

    class Logger {
        public:
            explicit Logger(const std::string &_filepath = LOG_FILEPATH);
            ~Logger();

            void operator<<(const std::string &message);

        private:
            std::ofstream _file;
    };
}

#endif
