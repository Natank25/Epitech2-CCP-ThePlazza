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

    JSON::JSON Stock::getStatus() const
    {
        JSON::JSON status = JSON::JSON::object();

        for (const auto &[name, quantity] : this->_ingredients) {
            status.set(name, quantity);
        }
        return status;
    }
} // namespace plazza
