/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-taha.alani
** File description:
** restaurant
*/

#ifndef RESTAURANT_HPP_
    #define RESTAURANT_HPP_

    #include <iostream>
    #include <csignal>
    #include <vector>
    #include "Irestaurant.hpp"

    class Restaurant : public Irestaurant {
        public:
            Restaurant() {};
            ~Restaurant() {};
            int getArguments(int ac, const char *av[]);
            int getCockingTime() const { return _cocking_time; };
            int getNbCooks() const { return _nb_cooks; };
            int getTime() const { return _time; };
            std::vector<PizzaCommand> getPizzaCommand() const { return _pizza_command; };
            int plazza_restaurant(const char *av[]);
        protected:
        private:
            int _cocking_time;
            int _nb_cooks;
            int _time;
            std::vector<PizzaCommand> _pizza_command;
    };

#endif /* !RESTAURANT_HPP_ */
