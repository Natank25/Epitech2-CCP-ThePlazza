/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** Process
*/

#include "Process.hpp"

#include <cstring>
#include <sys/wait.h>
#include <utility>

namespace plazza {
    Process::FailedForkException::FailedForkException(int errnoValue) :
        _errnoValue(errnoValue)
    {
    }

    const char *Process::FailedForkException::what() const noexcept
    {
        return std::strerror(_errnoValue);
    }

    Process::Process() :
        _pid(-1)
    {
    }

    Process::Process(Process &&other) noexcept :
        _pid(std::exchange(other._pid, -1)),
        _exitStatus(std::exchange(other._exitStatus, DEFAULT_EXIT_STATUS))
    {
    }

    Process &Process::operator=(Process &&other) noexcept
    {
        if (this != &other) {
            this->_pid = std::exchange(other._pid, -1);
            this->_exitStatus =
                std::exchange(other._exitStatus, DEFAULT_EXIT_STATUS);
        }
        return *this;
    }

    int Process::wait(int options)
    {
        if (waitpid(this->getPID(), &this->_exitStatus, options) == -1)
            throw std::runtime_error(
                std::string("waitpid failed: ") + std::strerror(errno));
        return this->_exitStatus;
    }

    int Process::getExitStatus() const
    {
        if (this->_exitStatus == DEFAULT_EXIT_STATUS)
            throw std::runtime_error(
                "Tried to get exit status but child didn't exit yet.");
        return this->_exitStatus;
    }
} // namespace plazza
