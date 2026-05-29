/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef COOK_HPP
    #define COOK_HPP
    #include <functional>
    #include "../Pizza/Pizza.hpp"
    #include "Safequeue.hpp"
    #include "Stock.hpp"

namespace plazza {

    class Cook {
    public:
        static void cookLoop(SafeQueue<PizzaOrder> &queue, Stock &stock,
            double multiplier,
            const std::function<void(const PizzaOrder &)> &onDone);
    };

} // namespace plazza

#endif // COOK_HPP
