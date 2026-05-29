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
    #include "Json.hpp"
    #include "Stock.hpp"

namespace plazza {
    class Kitchen;

    class Cook {
    public:
        explicit Cook(std::size_t id);
        void cookLoop(Kitchen &kitchen, Stock &stock, double multiplier,
            const std::function<void(const PizzaOrder &)> &onDone);

        std::size_t getId() const;

        JSON::JSON getStatus() const;

    private:
        bool _occupied;
        size_t _id;
    };

} // namespace plazza

#endif // COOK_HPP
