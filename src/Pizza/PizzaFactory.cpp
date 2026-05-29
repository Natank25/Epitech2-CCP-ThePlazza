/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#include "PizzaFactory.hpp"

#include <algorithm>
#include <ranges>

namespace plazza {
    Pizza PizzaFactory::createPizza(const std::string &name)
    {
        if (!doesPizzaExists(name))
            throw std::out_of_range("Pizza \"" + name + "\" doesn't exist.");
        return BUILTIN_PIZZAS_FACTORY.at(name)();
    }

    bool PizzaFactory::doesPizzaExists(std::string name)
    {
        std::ranges::transform(name, name.begin(), tolower);
        return BUILTIN_PIZZAS_FACTORY.contains(name);
    }

    const std::unordered_map<std::string, PizzaFactory::CreatePizza>
        PizzaFactory::BUILTIN_PIZZAS_FACTORY = {
            {"margarita", []() { return Pizza(MARGARITA_INGREDIENTS, 1000); }},
            {"regina", []() { return Pizza(REGINA_INGREDIENTS, 2000); }},
            {"americana", []() { return Pizza(AMERICANA_INGREDIENTS, 2000); }},
            {"fantasia", []() { return Pizza(FANTASIA_INGREDIENTS, 4000); }}};
} // namespace plazza
