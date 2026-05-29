/*
** EPITECH PROJECT, 2026
** plazza
** File description:
** DESCRIPTION
*/

#include <algorithm>

#include "Poller.hpp"

namespace plazza {
    Poller::Poller() = default;

    void Poller::pushBack(int fd)
    {
        this->_listeningFd.push_back(fd);
    }

    void Poller::popBack()
    {
        this->_listeningFd.pop_back();
    }

    int Poller::poll(int timeout)
    {
        std::vector<pollfd> pollFds = this->createPollFds();
        int result = ::poll(pollFds.data(), pollFds.size(), timeout);

        this->_pollResults.clear();
        this->_disconnectedFds.clear();

        for (size_t i = 0; i < pollFds.size(); ++i) {
            short int resultEvents = pollFds[i].revents;

            if (resultEvents == 0)
                continue;

            if (resultEvents & (POLLHUP | POLLERR | POLLNVAL))
                this->_disconnectedFds.push_back(this->_listeningFd[i]);
            else if (resultEvents & POLLIN)
                this->_pollResults.push_back(this->_listeningFd[i]);
        }

        return result;
    }

    const std::vector<int> &Poller::getPollResult()
    {
        return this->_pollResults;
    }

    const std::vector<int> &Poller::getDisconnectedFds()
    {
        return this->_disconnectedFds;
    }

    void Poller::removeFromFd(int fd)
    {
        auto it = std::ranges::remove(this->_listeningFd, fd).begin();
        this->_listeningFd.erase(it, this->_listeningFd.end());
    }

    std::vector<pollfd> Poller::createPollFds()
    {
        std::vector<pollfd> pollFds;

        pollFds.reserve(this->_listeningFd.size());
        std::ranges::transform(this->_listeningFd,
            std::back_inserter(pollFds),
            [](int fd) { return pollfd {fd, POLLIN, 0}; });
        return pollFds;
    }
} // namespace plazza
