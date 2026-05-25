/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#include "Stock.hpp"

#include <ranges>

namespace plazza {
    void Stock::refillIngredients()
    {
        for (auto &elem: _ingredients | std::views::values) {
            elem += 1;
        }
    }

    bool Stock::removeIngredientIfExists(unsigned int quantity,
        std::pair<std::string const, std::atomic<unsigned long>> &elem)
    {
        bool result = false;

        if (elem.second >= quantity) {
            elem.second -= quantity;
            result = true;
        }
        return result;
    }

    bool Stock::retrieveIngredient(const std::string &type, unsigned int quantity)
    {
        bool result = false;

        for (auto &elem: _ingredients) {
            if (elem.first == type) {
                result = removeIngredientIfExists(quantity, elem);
                break;
            }
        }
        return result;
    }
}
