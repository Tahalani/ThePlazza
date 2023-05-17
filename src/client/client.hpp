/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** Client
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include <iostream>
    #include <csignal>
    #include "../Irestaurant.hpp"

    class Client : public Irestaurant {
        public:
            Client() {};
            ~Client() {};
            int takeOrder(void);
            int checkOrder(void);
        private:
            std::string buffer;
    };

#endif /* !CLIENT_HPP_ */
