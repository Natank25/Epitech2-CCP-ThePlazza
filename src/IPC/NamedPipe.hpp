/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** NamedPipe
*/

#ifndef NAMEDPIPE_HPP
    #define NAMEDPIPE_HPP
    #include <fstream>
    #include <stdexcept>
    #include <string>
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
            if (!_writeStream.is_open())
                this->openWrite();
            _writeStream << value;
            return *this;
        }

        NamedPipe &operator>>(auto &value) {
            if (!_readStream.is_open())
                this->openRead();
            _readStream >> value;
            return *this;
        }

    private:
        std::string _path;
        std::ifstream _readStream;
        std::ofstream _writeStream;

        void openRead();
        void openWrite();

        static constexpr mode_t DEFAULT_FIFO_MODE = 0666;
    };
} // plazza

#endif
