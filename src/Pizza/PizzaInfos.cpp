/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#include "PizzaInfos.hpp"
namespace plazza {
    std::istream &operator>>(std::istream &stream, PizzaSize &pizzaSize)
    {
        std::string strSize;

        stream >> strSize;
        if (!PIZZA_SIZE_FROM_STR.contains(strSize))
            stream.setstate(std::ios::badbit);
        else
            pizzaSize = PIZZA_SIZE_FROM_STR.at(strSize);
        return stream;
    }
} // namespace plazza
