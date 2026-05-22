/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef STOCK_HPP
    #define STOCK_HPP
    #include <atomic>
    #include <map>
    #include <string>

namespace plazza {
    class Stock {
    public:
        void refillIngredients();
        void retrieveIngredient(std::string type);
    private:
        std::map<std::string, std::atomic<size_t>> _ingredients;
    };
}

#endif //STOCK_HPP