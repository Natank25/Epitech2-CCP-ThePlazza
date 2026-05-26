/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#include "Shell.hpp"

#include <iostream>
#include <sstream>

#include "Constants.hpp"

namespace plazza {
    Shell::Shell(std::vector<std::string> const &args) :
        _cookingMulti(1.0), _nbCooks(5), _refillTime(1000), _exitShell(false)
    {
        if (args.size() != 4)
            throw InvalidArgs("Invalid number of arguments.");
        std::istringstream cookingMultSs(args[1]);
        cookingMultSs >> _cookingMulti;
        if (!cookingMultSs || !cookingMultSs.eof())
            throw std::runtime_error("First argument is not a valid double");
        std::istringstream nbCooksSs(args[2]);
        nbCooksSs >> _nbCooks;
        if (!nbCooksSs || !nbCooksSs.eof() || nbCooksSs.str().starts_with("-"))
            throw std::runtime_error(
                "Second argument is not a valid unsigned int");
        std::istringstream refillTimeSs(args[3]);
        refillTimeSs >> _refillTime;
        if (!refillTimeSs || !refillTimeSs.eof() ||
            refillTimeSs.str().starts_with("-"))
            throw std::runtime_error(
                "Third argument is not a valid unsigned int");
    }

    int Shell::executeShell() const
    {
        std::string input;

        while (!std::cin.eof() && !getExitShell()) {
            std::cout << "> ";
            getline(std::cin, input);
            if (input.empty())
                continue;
        }
        return EPI_SUCCESS;
    }

    Shell::InvalidArgs::InvalidArgs(const std::string &msg)
    {
        _msg = msg;
    }

    const char *Shell::InvalidArgs::what() const noexcept
    {
        return _msg.c_str();
    }

    bool Shell::getExitShell() const
    {
        return _exitShell;
    }

    void Shell::exitShell()
    {
        _exitShell = true;
    }

    unsigned int Shell::getRefillTime() const
    {
        return _refillTime;
    }

    unsigned int Shell::getNbCooks() const
    {
        return _nbCooks;
    }

    double Shell::getCookingMulti() const { return _cookingMulti; }
} // namespace plazza