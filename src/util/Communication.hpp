/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Communication.hpp
*/

#ifndef COMMUNICATION_HPP_
#define COMMUNICATION_HPP_

#include <iostream>
#include <csignal>
#include <exception>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

namespace plazza {
    class CommunicationException : std::exception {
        public:
            explicit CommunicationException(std::string message);
            ~CommunicationException() override = default;

            [[nodiscard]] const char *what() const noexcept override;

        private:
            std::string _message;
    };

    class Communication {
        public:
            Communication();
            ~Communication();

        protected:
            template<typename T>
            struct Message {
                long type;
                pid_t sender;
                T data;
            };

            template<typename T>
            void sendMessage(const T &data, long target, size_t size = sizeof(T)) {
                Message<T> message = {
                        target,
                        getpid(),
                        data,
                };
                if (msgsnd(this->_queue_id, &message, size + sizeof(long) + sizeof(pid_t), 0) == -1) {
                    perror("msgsnd"); // TODO: remove debug
                    throw CommunicationException("msgsnd failed");
                }
            }

            template<typename T>
            Message<T> receiveMessage(size_t size = sizeof(T)) {
                Message<T> message;
                if (msgrcv(this->_queue_id, &message, size + sizeof(long) + sizeof(pid_t), getpid(), 0) == -1) {
                    perror("msgrcv"); // TODO: remove debug
                    throw CommunicationException("msgrcv failed");
                }
                return message;
            }

        private:
            key_t _key;
            int _queue_id;
    };
}

#endif
