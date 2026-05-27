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
        _readFailed(false),
        _ownsPath(true)
    {
        if (mkfifo(this->_path.c_str(), mode) == -1) {
            if (errno != EEXIST)
                throw FifoException(
                    std::string("mkfifo failed: ") + std::strerror(errno));
        }
    }

    NamedPipe::NamedPipe(NamedPipe &&other) noexcept :
        _path(std::move(other._path)),
        _readFd(std::exchange(other._readFd, -1)),
        _writeFd(std::exchange(other._writeFd, -1)),
        _readFailed(other._readFailed),
        _ownsPath(std::exchange(other._ownsPath, false))
    {
    }

    NamedPipe &NamedPipe::operator=(NamedPipe &&other) noexcept
    {
        if (this != &other) {
            if (this->_readFd != -1)
                close(this->_readFd);
            if (this->_writeFd != -1)
                close(this->_writeFd);
            if (this->_ownsPath && !this->_path.empty())
                unlink(this->_path.c_str());

            this->_path = std::move(other._path);
            this->_readFd = std::exchange(other._readFd, -1);
            this->_writeFd = std::exchange(other._writeFd, -1);
            this->_readFailed = other._readFailed;
            this->_ownsPath = std::exchange(other._ownsPath, false);
        }
        return *this;
    }

    NamedPipe::~NamedPipe()
    {
        if (this->_readFd != -1)
            close(this->_readFd);
        if (this->_writeFd != -1)
            close(this->_writeFd);
        if (this->_ownsPath && !this->_path.empty())
            unlink(this->_path.c_str());
    }

    const std::string &NamedPipe::getPath() const
    {
        return this->_path;
    }

    NamedPipe::operator bool() const
    {
        return !this->_readFailed;
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
