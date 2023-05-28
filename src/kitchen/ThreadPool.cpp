/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** ThreadPool.cpp
*/

#include <iostream>
#include "ThreadPool.hpp"

plazza::ThreadPool::ThreadPool(pid_t parentPid, const plazza::Configuration &config, std::shared_ptr<plazza::PlazzaIPC> ipc, std::shared_ptr<plazza::Logger> logger): _parentPid(parentPid), _config(config), _ipc(std::move(ipc)), _logger(std::move(logger)), _refill(std::thread(&ThreadPool::refillRoutine, this, config.getRefillTime())) {
    std::unique_lock<std::mutex> lock(this->_ingredients.second);
    for (int i = 0; i < config.getCooksPerKitchen(); i++) {
        this->_cooks.emplace_back(&ThreadPool::cookRoutine, this, i);
        this->_cooksStatus.first.emplace_back();
    }
}

plazza::ThreadPool::~ThreadPool() {
    std::unique_lock<std::mutex> lock(this->_pizzaQueue.second);

    while (!this->_pizzaQueue.first.empty()) {
        this->_pizzaQueue.first.pop();
    }
    this->_cookCond.notify_all();
    this->_exitCond.notify_all();
    for (auto &it : this->_cooks) {
        if (it.joinable()) {
            it.join();
        }
    }
    if (this->_refill.joinable()) {
        this->_refill.join();
    }
}

void plazza::ThreadPool::run(const Pizza &firstPizza) {
    std::unique_lock<std::mutex> lock(this->_pizzaQueue.second);
    this->_pizzaQueue.first.push(firstPizza);
    this->_cookCond.notify_one();
    lock.unlock();

    while (true) {
        Message<MessageType> type = this->_ipc->getNextMessage();
        if (type.data == MessageType::EXIT) {
            lock = std::unique_lock<std::mutex>(this->_pizzaQueue.second);
            while (!this->_pizzaQueue.first.empty()) {
                this->_pizzaQueue.first.pop();
            }
            this->_cookCond.notify_all();
            break;
        } else if (type.data == MessageType::PIZZA) {
            Pizza pizza;
            *this->_ipc >> pizza;
            if (!this->canAcceptPizza(pizza)) {
                lock = std::unique_lock<std::mutex>(this->_pizzaQueue.second);
                *this->_ipc << this->_parentPid << pizza;
                continue;
            }
            this->_pizzaQueue.first.push(pizza);
            this->_cookCond.notify_one();
        }
        // TODO: status
        // TODO: 5s inactivity
    }
}

bool plazza::ThreadPool::canAcceptPizza(const plazza::Pizza &pizza) {
    (void) pizza; // TODO: fix
    int totalPizzas = 0;
    time_t now = time(nullptr);

    std::unique_lock<std::mutex> lock(this->_cooksStatus.second);
    for (auto &it : this->_cooksStatus.first) {
        if (now - it.startTime <= (long) it.cookTime) {
            totalPizzas++;
        }
    }
    lock =  std::unique_lock<std::mutex>(this->_pizzaQueue.second);
    totalPizzas += (int) this->_pizzaQueue.first.size();
    return totalPizzas < this->_config.getCooksPerKitchen() * 2;
}

void plazza::ThreadPool::cookRoutine(int cookId) {
    while (true) {
        std::unique_lock<std::mutex> lock(this->_pizzaQueue.second);
        if (this->_pizzaQueue.first.empty()) {
            this->_cookCond.wait(lock);
        }
        if (this->_pizzaQueue.first.empty()) {
            return;
        }
        Pizza pizza = this->_pizzaQueue.first.front();
        this->_pizzaQueue.first.pop();
        lock.unlock();
        // TODO: Determine time
        // float millis = (float) this->_ingredients_per_pizza[pizza.type].second * 1000 * multiplier;
        float millis = 2000;
        lock = std::unique_lock<std::mutex>(this->_cooksStatus.second);
        this->_cooksStatus.first[cookId].type = pizza.type;
        this->_cooksStatus.first[cookId].size = pizza.size;
        this->_cooksStatus.first[cookId].cookTime = (long) millis;
        this->_cooksStatus.first[cookId].startTime = time(nullptr);
        lock.unlock();
        lock = std::unique_lock<std::mutex>(this->_pizzaQueue.second);
        std::cv_status result = this->_exitCond.wait_for(lock, std::chrono::milliseconds((long) millis));
        if (result == std::cv_status::no_timeout) {
            return;
        }
        pizza.cooked = true;
        *this->_ipc << this->_parentPid << pizza;
    }
}

void plazza::ThreadPool::refillRoutine(int refillTime) {
    while (true) {
        std::unique_lock<std::mutex> lock(this->_ingredients.second);
        std::cv_status status = this->_exitCond.wait_for(lock, std::chrono::milliseconds(refillTime));

        if (status == std::cv_status::no_timeout) {
            return;
        }
        for (size_t i = 0; i < this->_ingredients.first.size(); i += 1) {
            this->_ingredients.first[i] = std::min(MAX_INGREDIENTS, this->_ingredients.first[i] + 1);
            // TODO: Debug refill
        }
    }
}
