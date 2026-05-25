/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef SHELL_HPP
    #define SHELL_HPP
    #include <vector>
    #include <string>

namespace plazza {
    class Shell {
    public:
        explicit Shell(std::vector<std::string> const &args);

        class InvalidArgs : public std::exception {
        public:
            explicit InvalidArgs(const std::string &msg);

            [[nodiscard]] const char *what() const noexcept override;
        private:
            std::string _msg;
        };

    private:
        double _cookingMulti;
        unsigned int _nbCooks;
        unsigned int _refillTime;
    };
}
#endif // SHELL_HPP
