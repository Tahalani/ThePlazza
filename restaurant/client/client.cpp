/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** client
*/

#include "client.hpp"
#include <csignal>

int Client::checkOrder()
{
    std::string type;
    std::string size;
    std::string number;

    type = buffer.substr(0, buffer.find(" "));
    if (type == "regina" || type == "margarita" || type == "americana" || type == "fantasia") {
        buffer.erase(0, buffer.find(" ") + 1);
        size = buffer.substr(0, buffer.find(" "));
        if (size == "S" || size == "M" || size == "L" || size == "XL" || size == "XXL") {
            buffer.erase(0, buffer.find(" ") + 1);
            number = buffer.substr(0, buffer.find(" "));
            if (number.find_first_not_of("x0123456789") == std::string::npos) {
                std::cout << "type: " << type << std::endl;
                std::cout << "size: " << size << std::endl;
                std::cout << "number: " << number[1] << std::endl;
            } else
                std::cerr << "ERROR: In .pizzas parsing" << std::endl;
        } else
            std::cerr << "ERROR: In .pizzas parsing" << std::endl;
    } else
        std::cerr << "ERROR: In .pizzas parsing" << std::endl;
    return 0;
}

int Client::takeOrder(void)
{
    for (std::cout << "> "; std::getline(std::cin, buffer); std::cout << "> ") {
        if (buffer == "exit")
            return (0);
        else if (buffer == "Status")
            std::cout << "Status" << std::endl;
        else
            checkOrder();
    }
    return (0);
}
