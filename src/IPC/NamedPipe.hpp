/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** NamedPipe
*/

#ifndef NAMEDPIPE_HPP
    #define NAMEDPIPE_HPP
    #include <iomanip>
    #include <sstream>
    #include <stdexcept>
    #include <string>
    #include <unistd.h>
    #include <iostream>

namespace plazza {
    class NamedPipe {

    public:
        NamedPipe(const NamedPipe &) = delete;
        NamedPipe &operator=(const NamedPipe &) = delete;

        NamedPipe(NamedPipe &&other) noexcept;
        NamedPipe &operator=(NamedPipe &&other) noexcept;

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
            auto charRead = read(this->_readFd, buffer.data(), buffer.size());
            if (charRead > 0) {
                buffer.resize(static_cast<std::size_t>(charRead));
                while (!buffer.empty() && (buffer.back() == '\n' || buffer.back() == '\r'))
                    buffer.pop_back();
                std::cout << "Buffer: " << std::quoted(buffer) << std::endl;
                std::istringstream iss(buffer);
                iss >> value;
                this->_readFailed = !iss;
            } else {
                this->_readFailed = true;
            }
            return *this;
        }

        [[nodiscard]] operator bool() const;

    private:
        std::string _path;
        int _readFd;
        int _writeFd;
        bool _readFailed;
        bool _ownsPath;

        void openRead();
        void openWrite();

        static constexpr mode_t DEFAULT_FIFO_MODE = 0666;
        static constexpr size_t READ_BUFFER_SIZE = 512;
    };
} // plazza

#endif
