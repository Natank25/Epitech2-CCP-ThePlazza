/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#include "Stock.hpp"
#include <ranges>

#include <mutex>

#include "Ingredient.hpp"

namespace plazza {
    Stock::Stock()
    {
        _ingredients = {{DOUGH.name, 5},
            {TOMATO.name, 5},
            {GRUYERE.name, 5},
            {HAM.name, 5},
            {MUSHROOMS.name, 5},
            {STEAK.name, 5},
            {EGGPLANT.name, 5},
            {GOAT_CHEESE.name, 5},
            {CHIEF_LOVE.name, 5}};
    }

    void Stock::refillIngredients()
    {
        {
            std::unique_lock lock(_mutex);
            for (auto &[_, qty] : _ingredients)
                qty += 1;
        }
        _cv.notify_all();
    }

    bool Stock::retrieveIngredient(
        Ingredient const &ingredient, unsigned int quantity)
    {
        std::unique_lock lock(_mutex);
        _cv.wait(
            lock, [&] { return _ingredients.at(ingredient.name) >= quantity; });
        _ingredients.at(ingredient.name) -= quantity;
        return true;
    }
} // namespace plazza
