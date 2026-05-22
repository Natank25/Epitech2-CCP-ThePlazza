/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#include "Pizza.hpp"

#include <utility>

namespace plazza {
    Pizza::Pizza(std::vector<Ingredient> ingredients, double timeToCook) :
    _ingredients(std::move(ingredients)), _timeToCook(timeToCook)  {}
} // namespace plazza
