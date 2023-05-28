/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** kitchen
*/

#include <mutex>
#include "Kitchen.hpp"
#include "ThreadPool.hpp"

plazza::Kitchen::Kitchen(size_t id, Configuration &config, const PlazzaIPC &ipc) : _id(id), _config(config), _ipc(ipc), _parent_pid(getpid()), _kitchen_pid(0) {
    std::cout << "Kitchen ctor" << std::endl;
    this->_ingredients = {5, 5, 5, 5, 5, 5, 5, 5, 5};
}

plazza::Kitchen::~Kitchen() {
    std::cout << "Kitchen dtor in pid " << getpid() << std::endl;
}

size_t plazza::Kitchen::getId() const {
    return this->_id;
}

pid_t plazza::Kitchen::getKitchenPid() const {
    return this->_kitchen_pid;
}

void plazza::Kitchen::openKitchen(const Pizza &firstPizza) {
    pid_t pid = fork();

    if (pid == -1) {
        throw CommunicationException("fork failed");
    } else if (pid == 0) {
        std::cout << "Kitchen " << this->_id << " forked" << std::endl;
        this->run(firstPizza);
        exit(0);
    } else {
        std::cout << "Kitchen " << this->_id << " registed with pid " << pid << std::endl;
        this->_kitchen_pid = pid;
    }
}

void plazza::Kitchen::run(const Pizza &firstPizza) {
    ThreadPool pool(this->_parent_pid, this->_config, this->_ipc);

    pool.run(firstPizza);
}