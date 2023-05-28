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
#include "Logger.hpp"
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
            ThreadPool(pid_t parentPid, size_t kitchenId, const Configuration &config, std::shared_ptr<PlazzaIPC> ipc, std::shared_ptr<Logger> logger);
            ~ThreadPool();

            void run(const Pizza &firstPizza);

        private:
            void cookRoutine(int cookId);
            void refillRoutine(int refillTime);
            void idleRoutine(int idleTime);
            bool canAcceptPizza(const Pizza &pizza);
            void showStatus();
            long now();

            pid_t _parentPid;
            size_t _kitchenId;
            Configuration _config;
            std::shared_ptr<PlazzaIPC> _ipc;
            std::shared_ptr<Logger> _logger;
            Sharable<std::vector<CookStatus>> _cooksStatus;
            Sharable<std::queue<Pizza>> _pizzaQueue;
            Sharable<std::vector<int>> _ingredients;
            Sharable<long> _lastEvent;
            std::condition_variable _cookCond;
            std::condition_variable _exitCond;
            std::vector<std::thread> _cooks;
            std::thread _refill;
            std::thread _idle;
    };
}

#endif
