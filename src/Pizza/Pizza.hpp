/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef PIZZA_HPP
    #define PIZZA_HPP
    #include <string>
    #include <vector>

    #include "Ingredient.hpp"
    #include "PizzaInfos.hpp"

namespace plazza {
    class Pizza {
    public:
        Pizza(std::vector<Ingredient> ingredients, double timeToCook);

    private:
        std::vector<Ingredient> _ingredients;
        double _timeToCook;
    };

    struct PizzaOrder {
        PizzaSize size;
        std::string pizzaName;
    };

    struct PizzaOrderHasher {
        std::size_t operator()(const PizzaOrder &order) const;
    };

    std::istream &operator>>(std::istream &stream, PizzaOrder &pizzaOrder);

    std::ostream &operator<<(std::ostream &stream,
        const PizzaOrder &pizzaOrder);

    bool operator==(const PizzaOrder &lhs, const PizzaOrder &rhs);
} // namespace plazza

#endif //PIZZA_HPP
