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

        bool retrieveIngredient(const std::string& type, unsigned int quantity);

    private:
        static bool removeIngredientIfExists(unsigned int quantity,
            std::pair<std::string const, std::atomic<unsigned long>> &elem);

        std::map<std::string, std::atomic<size_t>> _ingredients;
    };
}

#endif //STOCK_HPP