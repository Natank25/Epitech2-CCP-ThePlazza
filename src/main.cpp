/*
** EPITECH PROJECT, 2026
** Plazza
** File description:
** DESCRIPTION
*/

#include <deque>
#include <iostream>
#include <ostream>

#include "Constants.hpp"
#include "Shell/Shell.hpp"

int main(int ac, char **av)
{
    std::vector<std::string> args(av, av + ac);

    plazza::Shell s(args);
    return s.executeShell();
}
