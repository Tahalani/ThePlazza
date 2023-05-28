/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Configuration.hpp
*/

#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#define IDLE_TIME 5000

#include <exception>
#include <sstream>
#include <string>
#include <vector>
#include "PizzaRecipe.hpp"

namespace plazza {
    class ConfigurationException : std::exception {
        public:
            explicit ConfigurationException(std::string message);

            [[nodiscard]] const char *what() const noexcept override;

        private:
            std::string _message;
    };

    class Configuration {
        public:
            Configuration(int argc, char const *argv[], const std::string &configFolder);

            [[nodiscard]] float getTimeMultiplier() const;
            [[nodiscard]] int getCooksPerKitchen() const;
            [[nodiscard]] int getRefillTime() const;
            [[nodiscard]] PizzaRecipe &getRecipe(const std::string &name);

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
                std::unordered_map<std::string, PizzaRecipe> _pizzaRecipes;
    };
}

#endif
