/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** ThreadPool.cpp
*/

#include "Cook.hpp"
#include "ThreadPool.hpp"

plazza::ThreadPool::ThreadPool(pid_t parentPid, const plazza::Configuration &config, const plazza::Communication &ipc): _parentPid(parentPid), _config(config), _ipc(ipc), _refill(std::thread(&ThreadPool::refillRoutine, this, config.getRefillTime())) {
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
    lock.unlock();
    this->_cookCond.notify_one();

    while (true) {
        auto type = this->_ipc.receiveMessage<plazza::MessageType>();
        if (type.data == MessageType::PIZZA) {
            auto pizza = this->_ipc.receiveMessage<plazza::Pizza>();
            if (!this->canAcceptPizza(pizza.data)) {
                lock = std::unique_lock<std::mutex>(this->_pizzaQueue.second);
                this->_ipc.sendMessage(plazza::MessageType::PIZZA, this->_parentPid);
                this->_ipc.sendMessage(pizza, this->_parentPid);
                continue;
            }
            this->_pizzaQueue.first.push(pizza.data);
            lock.unlock();
            this->_cookCond.notify_one();
        } else if (type.data == MessageType::EXIT) {
            lock = std::unique_lock<std::mutex>(this->_pizzaQueue.second);
            while (!this->_pizzaQueue.first.empty()) {
                this->_pizzaQueue.first.pop();
            }
            lock.unlock();
            this->_cookCond.notify_all();
            break;
        }
    }
}

bool plazza::ThreadPool::canAcceptPizza(const plazza::Pizza &pizza) {
    int totalPizzas = 0;
    time_t now = time(nullptr);

    for (auto &it : this->_cooksStatus) {
        std::unique_lock<std::mutex> lock(it.second);
        if (now - it.first.startTime <= (long) it.first.cookTime) {
            totalPizzas++;
        }
    }
    std::unique_lock<std::mutex> lock(this->_pizzaQueue.second);
    totalPizzas += (int) this->_pizzaQueue.first.size();
    return totalPizzas < this->_config.getCooksPerKitchen() * 2;
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
        this->_cooksStatus[cookId].first.cookTime = (long) millis;
        this->_cooksStatus[cookId].first.startTime = time(nullptr);
        lock.unlock();
        std::cv_status result = this->_cookCond.wait_for(lock, std::chrono::milliseconds((long) millis));
        if (result == std::cv_status::no_timeout) {
            return;
        }
        this->_ipc.sendMessage(MessageType::PIZZA, this->_parentPid);
        this->_ipc.sendMessage(pizza, this->_parentPid);
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
