/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** kitchen
*/

#include <thread>
#include <mutex>
#include "Communication.hpp"
#include "Kitchen.hpp"

plazza::Kitchen::Kitchen(size_t id, Configuration &config, const Communication &ipc, const Pizza &firstPizza) : _id(id), _ipc(ipc), _parent_pid(getppid())
{
    std::unordered_map<Ingredients, int> ReginaIngr = {
            {Ingredients::Dough, 1},
            {Ingredients::Tomato, 1},
            {Ingredients::Gruyere, 1},
            {Ingredients::Ham, 1},
            {Ingredients::Mushrooms, 1},
    };
    std::unordered_map<Ingredients, int> MargaritaIngr = {
            {Ingredients::Dough, 1},
            {Ingredients::Tomato, 1},
            {Ingredients::Gruyere, 1},
    };
    std::unordered_map<Ingredients, int> AmericanaIngr = {
            {Ingredients::Dough, 1},
            {Ingredients::Tomato, 1},
            {Ingredients::Gruyere, 1},
            {Ingredients::Steak, 1},
    };
    std::unordered_map<Ingredients, int> FantasiaIngr = {
            {Ingredients::Dough, 1},
            {Ingredients::Tomato, 1},
            {Ingredients::Eggplant, 1},
            {Ingredients::GoatCheese, 1},
            {Ingredients::ChiefLove, 1},
    };

    this->_ingredients = {5, 5, 5, 5, 5, 5, 5, 5, 5};
    this->_ingredients_per_pizza = {
            {PizzaType::Regina, {ReginaIngr, 2}},
            {PizzaType::Margarita, {MargaritaIngr, 1}},
            {PizzaType::Americana, {AmericanaIngr, 2}},
            {PizzaType::Fantasia, {FantasiaIngr, 4}},
    };

    for (int i = 0; i <= config.getCooksPerKitchen(); i++) {
        this->_cooks.emplace_back(&Kitchen::kitchenRoutine, this, config.getTimeMultiplier());
    }
    this->_refill = std::move(std::thread(&Kitchen::refillRoutine, this, config.getRefillTime()));
    this->_pizzaQueue.push(firstPizza);
    this->_cookCondVar.notify_one();

    /*while (1) {
        auto type = this->_ipc.receiveMessage<plazza::MessageType>();

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
        }
    }*/
}

plazza::Kitchen::~Kitchen()
{
    this->_refill.join();
    for (auto &cook : this->_cooks) {
        cook.join();
    }
}

void plazza::Kitchen::kitchenRoutine(float multiplier)
{
    float millis = 0;
    std::unique_lock<std::mutex> lock(this->_kitchenMutex);

    while (true) {
        this->_cookCondVar.wait(lock);
        if (this->_pizzaQueue.empty()) {
            lock.unlock();
            return;
        }
        Pizza pizza = this->_pizzaQueue.front();
        this->_pizzaQueue.pop();
        millis = (float) this->_ingredients_per_pizza[pizza.type].second * 1000 * multiplier;
        auto result = this->_cookCondVar.wait_for(lock, std::chrono::milliseconds((int) millis));
        if (result == std::cv_status::no_timeout) {
            return;
        }
        /*this->_ipc.sendMessageRaw(MessageType::PIZZA, this->_parent_pid);
        this->_ipc.sendMessage(pizza, this->_parent_pid);*/
    }
}

void plazza::Kitchen::refillRoutine(int refillTime)
{
    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(refillTime));
        for (size_t i = 0; i < _ingredients.size(); i += 1) {
            if (_ingredients[i] < 5) {
                _ingredients[i] += 1;
                std::cout << "Refill ingredient " << std::endl;
            }
        }
    }
}
