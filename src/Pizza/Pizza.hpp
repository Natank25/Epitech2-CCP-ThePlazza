/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef PIZZA_HPP
    #define PIZZA_HPP
#include <string>
#include <vector>

    #include "Ingredient.hpp"
    #include "PizzaInfos.hpp"

namespace plazza {
    class Pizza {
    public:
        Pizza(std::vector<Ingredient> ingredients, double timeToCook);
    private:
        std::vector<Ingredient> _ingredients;
        double _timeToCook;
    };

    struct PizzaOrder {
        PizzaSize size;
        std::string pizzaName;
    };
}

#endif //PIZZA_HPP