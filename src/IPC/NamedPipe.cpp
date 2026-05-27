/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** NamedPipe
*/

#include "NamedPipe.hpp"

#include <cstring>
#include <unistd.h>
#include <sys/stat.h>

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

    std::ifstream NamedPipe::getInputStream() const
    {
        std::ifstream stream(this->_path);
        if (!stream)
            throw FifoException(std::string("Failed to open input stream: ") +
                                std::strerror(errno));
        return stream;
    }

    std::ofstream NamedPipe::getOutputStream() const
    {
        std::ofstream stream(this->_path);
        if (!stream)
            throw FifoException(std::string("Failed to open output stream: ") +
                                std::strerror(errno));
        return stream;
    }
} // plazza
