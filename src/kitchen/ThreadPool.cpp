/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** ThreadPool.cpp
*/

#include "Cook.hpp"
#include "ThreadPool.hpp"

plazza::ThreadPool::ThreadPool(pid_t parentPid, const plazza::Configuration &config): _parentPid(parentPid), _config(config), _refill(std::thread(&ThreadPool::refillRoutine, this, config.getRefillTime())) {
    for (int i = 0; i <= config.getCooksPerKitchen(); i++) {
        this->_cooks.emplace_back(&ThreadPool::cookRoutine, this, i);
    }
}

plazza::ThreadPool::~ThreadPool() {
    std::unique_lock<std::mutex> lock(this->_pizzaQueue.second);

    while (!this->_pizzaQueue.first.empty()) {
        this->_pizzaQueue.first.pop();
    }
    lock.unlock();
    this->_cookCond.notify_all();
    this->_refillCond.notify_all();
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

    while (true) {
        // TODO Main thread process
        /*auto type = this->_ipc.receiveMessage<plazza::MessageType>();

        if (type == MessageType::PIZZA) {
            auto pizza = this->_ipc.receiveMessage<plazza::Pizza>();
            this->_pizzaQueue.push(pizza);
            this->_cookCondVar.notify_one();
            this->_ipc.sendMessageRaw(plazza::MessageType::PIZZA_RESPONSE, this->_parent_pid);
            this->_ipc.sendMessageRaw<bool>(true, this->_parent_pid);
        } else if (type == MessageType::EXIT) {
            while (!this->_pizzaQueue.empty()) {
                this->_pizzaQueue.pop();
            }
            this->_cookCondVar.notify_all();
        }*/
    }
}

void plazza::ThreadPool::cookRoutine(int cookId) {
    while (true) {
        std::unique_lock<std::mutex> lock(this->_pizzaQueue.second);
        this->_cookCond.wait(lock);
        if (this->_pizzaQueue.first.empty()) {
            return;
        }
        Pizza pizza = this->_pizzaQueue.first.front();
        this->_pizzaQueue.first.pop();
        lock.unlock();
        // TODO: Determine time
        // float millis = (float) this->_ingredients_per_pizza[pizza.type].second * 1000 * multiplier;
        float millis = 2000;
        lock = std::unique_lock<std::mutex>(this->_cooksStatus[cookId].second);
        this->_cooksStatus[cookId].first.pizza = pizza;
        this->_cooksStatus[cookId].first.cookTime = millis;
        this->_cooksStatus[cookId].first.startTime = time(nullptr);
        lock.unlock();
        std::cv_status result = this->_cookCond.wait_for(lock, std::chrono::milliseconds((int) millis));
        if (result == std::cv_status::no_timeout) {
            return;
        }
        // TODO: Send cooked pizza
        // this->_ipc.sendMessageRaw(MessageType::PIZZA, this->_parent_pid);
        // this->_ipc.sendMessage(pizza, this->_parent_pid);
    }
}

void plazza::ThreadPool::refillRoutine(int refillTime) {
    while (true) {
        std::unique_lock<std::mutex> lock(this->_ingredients.second);
        std::cv_status status = this->_refillCond.wait_for(lock, std::chrono::milliseconds(refillTime));

        if (status == std::cv_status::no_timeout) {
            return;
        }
        for (size_t i = 0; i < this->_ingredients.first.size(); i += 1) {
            this->_ingredients.first[i] = std::min(5, this->_ingredients.first[i] + 1);
            // TODO define constant for max ingredients
        }
    }
}
