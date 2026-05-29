/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef STOCK_HPP
    #define STOCK_HPP
    #include <condition_variable>
    #include <mutex>
    #include <unordered_map>
    #include "Ingredient.hpp"
    #include "Json.hpp"

namespace plazza {
    class Stock {
    public:
        Stock() = default;

        void refillIngredients();

        bool retrieveIngredient(
            Ingredient const &ingredient, unsigned int quantity);

        [[nodiscard]] JSON::JSON getStatus() const;

    private:
        std::unordered_map<std::string, unsigned int> _ingredients {
            {DOUGH.name, 5},
            {TOMATO.name, 5},
            {GRUYERE.name, 5},
            {HAM.name, 5},
            {MUSHROOMS.name, 5},
            {STEAK.name, 5},
            {EGGPLANT.name, 5},
            {GOAT_CHEESE.name, 5},
            {CHIEF_LOVE.name, 5}};
        std::mutex _mutex;
        std::condition_variable _cv;
    };
} // namespace plazza

#endif // STOCK_HPP
