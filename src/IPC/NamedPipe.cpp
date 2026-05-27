/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** NamedPipe
*/

#include "NamedPipe.hpp"

#include <cerrno>
#include <cstring>
#include <utility>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


namespace plazza {
    NamedPipe::FifoException::FifoException(const std::string &message) :
        std::runtime_error(message)
    {
    }

    NamedPipe::NamedPipe(std::string path, mode_t mode) :
        _path(std::move(path)),
        _readFd(-1),
        _writeFd(-1),
        _readStatus(false)
    {
        if (mkfifo(this->_path.c_str(), mode) == -1) {
            if (errno != EEXIST)
                throw FifoException(
                    std::string("mkfifo failed: ") + std::strerror(errno));
        }
    }

    NamedPipe::~NamedPipe()
    {
        unlink(this->_path.c_str());
    }

    const std::string &NamedPipe::getPath() const
    {
        return this->_path;
    }

    NamedPipe::operator bool() const
    {
        return this->_readStatus;
    }

    void NamedPipe::openRead()
    {
        this->_readFd = open(this->_path.c_str(), O_RDONLY);
        if (this->_readFd == -1)
            throw FifoException(std::string("Failed to open read stream: ") +
                                std::strerror(errno));
    }

    void NamedPipe::openWrite()
    {
        this->_writeFd = open(this->_path.c_str(), O_WRONLY);
        if (this->_writeFd == -1)
            throw FifoException(std::string("Failed to open write stream: ") +
                                std::strerror(errno));
    }
} // plazza
