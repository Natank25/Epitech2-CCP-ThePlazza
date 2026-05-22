/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef PIZZAFACTORY_HPP
    #define PIZZAFACTORY_HPP
    #include <functional>
    #include <memory>
    #include <unordered_map>

    #include "Ingredient.hpp"
    #include "../src/Pizza/Pizza.hpp"

namespace plazza {
    static const std::vector<Ingredient> MARGARITA_INGREDIENTS = {
        DOUGH,
        TOMATO,
        GRUYERE
    };

    static const std::vector<Ingredient> REGINA_INGREDIENTS = {
        DOUGH,
        TOMATO,
        GRUYERE,
        HAM,
        MUSHROOMS
    };

    static const std::vector<Ingredient> AMERICANA_INGREDIENTS = {
        DOUGH,
        TOMATO,
        GRUYERE,
        STEAK
    };

    static const std::vector<Ingredient> FANTASIA_INGREDIENTS = {
        DOUGH,
        TOMATO,
        EGGPLANT,
        GOAT_CHEESE,
        CHIEF_LOVE
    };

    class PizzaFactory {
    public:
        static Pizza createPizza(std::string name);
    };

    using CreatePizza = std::function<Pizza()>;
    static const std::unordered_map<std::string, CreatePizza>
        BUILTIN_PIZZAS_FACTORY = {
            {"Margarita", [](){ return Pizza(MARGARITA_INGREDIENTS, 1000); }},
            {"Regina", []() { return Pizza(REGINA_INGREDIENTS, 2000); }},
            {"Americana", []() { return Pizza(AMERICANA_INGREDIENTS, 2000); }},
            {"Fantasia", []() { return Pizza(FANTASIA_INGREDIENTS, 4000); }}
        };
}

#endif // PIZZAFACTORY_HPP
