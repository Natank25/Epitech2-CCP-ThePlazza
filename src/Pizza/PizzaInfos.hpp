/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef PIZZAINFOS_HPP
    #define PIZZAINFOS_HPP

    #include <iostream>
#include <unordered_map>

namespace plazza {
    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    std::istream &operator>>(std::istream &stream, PizzaSize &pizzaSize);

    static const std::unordered_map<std::string, PizzaSize>
        PIZZA_SIZE_FROM_STR = {
            {"S", S},
            {"M", M},
            {"L", L},
            {"XL", XL},
            {"XXL", XXL},
        };
} // namespace plazza

#endif // PIZZAINFOS_HPP
