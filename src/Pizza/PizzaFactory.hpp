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
    #include "Pizza.hpp"

namespace plazza {
    static const std::vector MARGARITA_INGREDIENTS = {
        DOUGH,
        TOMATO,
        GRUYERE
    };

    static const std::vector REGINA_INGREDIENTS = {
        DOUGH,
        TOMATO,
        GRUYERE,
        HAM,
        MUSHROOMS
    };

    static const std::vector AMERICANA_INGREDIENTS = {
        DOUGH,
        TOMATO,
        GRUYERE,
        STEAK
    };

    static const std::vector FANTASIA_INGREDIENTS = {
        DOUGH,
        TOMATO,
        EGGPLANT,
        GOAT_CHEESE,
        CHIEF_LOVE
    };

    class PizzaFactory {
    public:
        using CreatePizza = std::function<Pizza()>;

        static Pizza createPizza(const std::string &name);
        static bool doesPizzaExists(std::string name);
    private:
        static const std::unordered_map<std::string, CreatePizza>
            BUILTIN_PIZZAS_FACTORY;;
    };

} // namespace plazza

#endif // PIZZAFACTORY_HPP
