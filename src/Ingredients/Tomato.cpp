/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#include "Tomato.hpp"
#include "Constants.hpp"

namespace plazza {
    std::string Tomato::getImagePath() const
    {
        return std::string(TOMATO_PATH);
    }

    std::string_view Tomato::getName() const
    {
        return TOMATO_NAME;
    }
}
