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

namespace plazza {
    NamedPipe::FifoException::FifoException(const std::string &message) :
        std::runtime_error(message)
    {
    }

    NamedPipe::NamedPipe(std::string path, mode_t mode) :
        _path(std::move(path))
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

    void NamedPipe::openRead()
    {
        _readStream.open(this->_path);
        if (!_readStream.is_open())
            throw FifoException(std::string("Failed to open read stream: ") +
                                std::strerror(errno));
    }

    void NamedPipe::openWrite()
    {
        _writeStream.open(this->_path);
        if (!_writeStream.is_open())
            throw FifoException(std::string("Failed to open write stream: ") +
                                std::strerror(errno));
    }
} // plazza


