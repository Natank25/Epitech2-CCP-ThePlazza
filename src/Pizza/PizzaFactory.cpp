/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#include "PizzaFactory.hpp"

namespace plazza {
    Pizza PizzaFactory::createPizza(const std::string &name)
    {
        if (!doesPizzaExists(name))
            throw std::out_of_range("Pizza \"" + name + "\" doesn't exist.");
        return BUILTIN_PIZZAS_FACTORY.at(name)();
    }

    bool PizzaFactory::doesPizzaExists(const std::string &name)
    {
        return BUILTIN_PIZZAS_FACTORY.contains(name);
    }

    const std::unordered_map<std::string, PizzaFactory::CreatePizza>
    PizzaFactory::BUILTIN_PIZZAS_FACTORY = {
        {"Margarita", []() { return Pizza(MARGARITA_INGREDIENTS, 1000); }},
        {"Regina", []() { return Pizza(REGINA_INGREDIENTS, 2000); }},
        {"Americana", []() { return Pizza(AMERICANA_INGREDIENTS, 2000); }},
        {"Fantasia", []() { return Pizza(FANTASIA_INGREDIENTS, 4000); }}
    };
}
