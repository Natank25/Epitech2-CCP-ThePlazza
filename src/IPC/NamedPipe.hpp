/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** NamedPipe
*/

#ifndef NAMEDPIPE_HPP
    #define NAMEDPIPE_HPP
    #include <array>
    #include <fstream>
    #include <sstream>
    #include <stdexcept>
    #include <string>
    #include <unistd.h>
    #include <sys/stat.h>

namespace plazza {
    class NamedPipe {

    public:
        class FifoException : public std::runtime_error {
        public:
            explicit FifoException(const std::string &message);
        };

        explicit NamedPipe(std::string path, mode_t mode = DEFAULT_FIFO_MODE);

        ~NamedPipe();

        [[nodiscard]] const std::string &getPath() const;

        NamedPipe &operator<<(auto value) {
            if (_writeFd == -1)
                this->openWrite();
            std::ostringstream oss;
            oss << value;
            std::string text = oss.str();
            write(this->_writeFd, text.c_str(), text.size());
            return *this;
        }

        NamedPipe &operator>>(auto &value) {
            if (_readFd == -1)
                this->openRead();
            std::string buffer{};
            buffer.resize(READ_BUFFER_SIZE);
            read(this->_readFd, buffer.data(), buffer.size());
            std::istringstream iss(buffer);
            iss >> value;
            this->_readStatus = iss.fail();
            return *this;
        }

        [[nodiscard]] operator bool() const;

    private:
        std::string _path;
        int _readFd;
        int _writeFd;
        bool _readStatus;

        void openRead();
        void openWrite();

        static constexpr mode_t DEFAULT_FIFO_MODE = 0666;
        static constexpr size_t READ_BUFFER_SIZE = 512;
    };
} // plazza

#endif
