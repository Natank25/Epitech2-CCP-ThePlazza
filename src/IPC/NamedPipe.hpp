/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#ifndef NAMEDPIPE_HPP
    #define NAMEDPIPE_HPP
    #include <stdexcept>
    #include <fstream>

namespace plazza {
    class NamedPipe {

    public:
        class FifoException : public std::runtime_error {
        public:
            explicit FifoException(const std::string &message);
        };

        explicit NamedPipe(std::string path, mode_t mode = 0666);

        ~NamedPipe();

        [[nodiscard]] const std::string &getPath() const;

        [[nodiscard]] std::ifstream getInputStream() const;

        [[nodiscard]] std::ofstream getOutputStream() const;

    private:
        std::string _path;
    };
} // plazza

#endif
