/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
    #define PARSING_HPP_

    #include <iostream>
    #include <csignal>
    #include <vector>

enum PizzaType {
    Regina,
    Margarita,
    Americana,
    Fantasia
};

enum PizzaSize {
    S,
    M,
    L,
    XL,
    XXL
};

struct PizzaCommand {
    PizzaType type;
    PizzaSize size;
    int quantity;
};

    class Parsing {
        public:
            Parsing() {};
            ~Parsing() {};
            int getArguments(int ac, char **av);
            int getCockingTime() const { return _cocking_time; };
            int getNbCooks() const { return _nb_cooks; };
            int getTime() const { return _time; };
            std::vector<PizzaCommand> getPizzaCommand() const { return _pizza_command; };
        private:
            int _cocking_time;
            int _nb_cooks;
            int _time;
            std::vector<PizzaCommand> _pizza_command;
    };

#endif /* !PARSING_HPP_ */
