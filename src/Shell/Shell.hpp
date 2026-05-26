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

        [[nodiscard]] int executeShell() const;

        class InvalidArgs : public std::exception {
        public:
            explicit InvalidArgs(const std::string &msg);

            [[nodiscard]] const char *what() const noexcept override;
        private:
            std::string _msg;
        };

        [[nodiscard]] bool getExitShell() const;
        void exitShell();

        [[nodiscard]] unsigned int getRefillTime() const;
        [[nodiscard]] unsigned int getNbCooks() const;
        [[nodiscard]] double getCookingMulti() const;

    private:
        double _cookingMulti;
        unsigned int _nbCooks;
        unsigned int _refillTime;
        bool _exitShell;
    };
}
#endif // SHELL_HPP
