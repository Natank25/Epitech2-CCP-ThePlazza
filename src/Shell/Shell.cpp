/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#include "Shell.hpp"

#include <iostream>
#include <sstream>

namespace plazza {
    Shell::Shell(std::vector<std::string> const &args) :
        _cookingMulti(1.0),
        _nbCooks(5),
        _refillTime(1000)
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
            throw std::runtime_error("Second argument is not a valid unsigned int");
        std::istringstream refillTimeSs(args[3]);
        refillTimeSs >> _refillTime;
        if (!refillTimeSs || !refillTimeSs.eof() || refillTimeSs.str().starts_with("-"))
            throw std::runtime_error("Third argument is not a valid unsigned int");
    }

    Shell::InvalidArgs::InvalidArgs(const std::string &msg)
    {
        _msg = msg;
    }

    const char * Shell::InvalidArgs::what() const noexcept
    {
        return _msg.c_str();
    }
} // plazza