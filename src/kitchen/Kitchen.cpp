/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** kitchen
*/

#include <mutex>
#include <utility>
#include "Kitchen.hpp"
#include "ThreadPool.hpp"

plazza::Kitchen::Kitchen(size_t id, Configuration &config, std::shared_ptr<PlazzaIPC> ipc, std::shared_ptr<Logger> logger) : _id(id), _config(config), _ipc(std::move(ipc)), _logger(std::move(logger)), _parent_pid(getpid()), _kitchen_pid(0) {

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
        this->run(firstPizza);
        exit(0);
    } else {
        this->_kitchen_pid = pid;
    }
}

void plazza::Kitchen::run(const Pizza &firstPizza) {
    ThreadPool pool(this->_parent_pid, this->_config, this->_ipc, this->_logger);

    pool.run(firstPizza);
}