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

struct PizzaCommand {
    int _cocking_time;
    int _nb_cooks;
    int _time;
};

    class Parsing {
        public:
            Parsing() {};
            ~Parsing() {};
            int getArguments(int ac, char **av);
            int getCockingTime() const { return _cocking_time; };
            int getNbCooks() const { return _nb_cooks; };
            int getTime() const { return _time; };
        private:
            int _cocking_time;
            int _nb_cooks;
            int _time;
    };

#endif /* !PARSING_HPP_ */
