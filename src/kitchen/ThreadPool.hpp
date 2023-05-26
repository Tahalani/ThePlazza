/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** ThreadPool.hpp
*/

#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_

#include <condition_variable>
#include <queue>
#include <thread>
#include <vector>
#include "Configuration.hpp"
#include "PizzaData.hpp"
#include "PlazzaIPC.hpp"

namespace plazza {
    struct CookStatus {
        std::string type;
        PizzaSize size;
        long cookTime;
        time_t startTime;
    };

    class ThreadPool {
        template<typename T>
        using Sharable = std::pair<T, std::mutex>;

        public:
            ThreadPool(pid_t parentPid, const Configuration &config, const PlazzaIPC &ipc);
            ~ThreadPool();

            void run(const Pizza &firstPizza);

        private:
            void cookRoutine(int cookId);
            void refillRoutine(int refillTime);
            bool canAcceptPizza(const Pizza &pizza);

            pid_t _parentPid;
            Configuration _config;
            PlazzaIPC _ipc;
            std::vector<std::thread> _cooks;
            std::vector<Sharable<CookStatus>> _cooksStatus;
            Sharable<std::queue<Pizza>> _pizzaQueue;
            Sharable<std::vector<int>> _ingredients;
            std::thread _refill;
            std::condition_variable _refillCond;
            std::condition_variable _cookCond;
    };
}

#endif
