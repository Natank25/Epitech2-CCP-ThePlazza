/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef KITCHEN_HPP
    #define KITCHEN_HPP
    #include <queue>

    #include "Cook.hpp"
    #include "Pizza.hpp"
    #include "Stock.hpp"

namespace plazza {
    class Kitchen {
    public:
        explicit Kitchen(std::size_t _numberCooks);
    private:
        void refill(double deltaTime);

        double _timeSinceLastRefill;
        std::vector<Cook> _cooks;
        std::queue<PizzaOrder> _orders;
        Stock _stock;
    };
}

#endif //KITCHEN_HPP