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

namespace plazza {
    class Stock {
    public:
        Stock();

        void refillIngredients();
        bool retrieveIngredient(
            Ingredient const &ingredient, unsigned int quantity);

    private:
        std::unordered_map<std::string, unsigned int> _ingredients;
        std::mutex _mutex;
        std::condition_variable _cv;
    };
} // namespace plazza

#endif // STOCK_HPP
