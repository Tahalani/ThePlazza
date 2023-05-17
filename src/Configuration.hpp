/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Configuration.hpp
*/

#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <exception>
#include <sstream>
#include <string>

namespace plazza {
    class ConfigurationException : std::exception {
        public:
            explicit ConfigurationException(std::string message);
            ~ConfigurationException() override = default;

            [[nodiscard]] const char *what() const noexcept override;

        private:
            std::string _message;
    };

    class Configuration {
        public:
            Configuration(int argc, char const *argv[]);
            ~Configuration() = default;

            [[nodiscard]] float getTimeMultiplier() const;
            [[nodiscard]] int getCooksPerKitchen() const;
            [[nodiscard]] int getRefillTime() const;

        template<typename T>
        T parse(const std::string &str)
        {
            std::stringstream stream(str);
            T value;

            stream >> value;
            if (stream.fail() || !stream.eof()) {
                throw ConfigurationException(str + ": Invalid argument");
            }
            return value;
        }

        private:
            float _timeMultiplier;
            int _cooksPerKitchen;
            int _refillTime;
    };
}

#endif