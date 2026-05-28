/*
** EPITECH PROJECT, 2026
** plazza
** File description:
** DESCRIPTION
*/

#ifndef POLLER_HPP
    #define POLLER_HPP
    #include <sys/poll.h>
    #include <vector>

namespace plazza {
    class Poller {
    public:
        Poller();

        void pushBack(int fd);

        void popBack();

        int poll(int timeout = -1);

        const std::vector<int> &getPollResult();

        const std::vector<int> &getDisconnectedFds();

        void removeFromFd(int fd);

    private:
        std::vector<pollfd> createPollFds();

        std::vector<int> _listeningFd;

        std::vector<int> _pollResults;
        std::vector<int> _disconnectedFds;
    };
} // namespace plazza

#endif
