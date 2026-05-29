/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** NamedPipe
*/

#ifndef NAMEDPIPE_HPP
    #define NAMEDPIPE_HPP
    #include <iomanip>
    #include <iostream>
    #include <sstream>
    #include <stdexcept>
    #include <string>
    #include <unistd.h>

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

        NamedPipe &operator<<(const auto &value)
        {
            if (_writeFd == -1)
                this->openWrite();
            std::ostringstream oss;
            oss << value << '\n';
            std::string text = oss.str();
            write(this->_writeFd, text.c_str(), text.size());
            return *this;
        }

        NamedPipe &operator>>(auto &value)
        {
            auto line = this->getLine();
            std::istringstream iss(line);
            iss >> value;
            this->_readFailed = !iss;

            return *this;
        }

        std::string getLine();

        [[nodiscard]] operator bool() const;

        [[nodiscard]] int getReadFd() const;

        [[nodiscard]] int getWriteFd() const;

        void openRead();

        void openWrite();

        [[nodiscard]] bool isReadable() const;

    private:
        std::string _path;
        int _readFd;
        int _writeFd;
        bool _readFailed;
        bool _ownsPath;
        std::string _readBuffer;

        void fillBufferUntilNewline();

        static constexpr mode_t DEFAULT_FIFO_MODE = 0666;
        static constexpr size_t READ_BUFFER_SIZE = 512;
    };
} // namespace plazza

#endif
