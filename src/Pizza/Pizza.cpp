/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#include "Pizza.hpp"

#include <algorithm>
#include <ranges>
#include <utility>

#include "PizzaFactory.hpp"

namespace plazza {
    Pizza::Pizza(std::vector<Ingredient> ingredients, double timeToCook) :
        _ingredients(std::move(ingredients)), _timeToCook(timeToCook)
    {
    }

    std::vector<Ingredient> Pizza::getIngredients()
    {
        return _ingredients;
    }

    double Pizza::getTimeToCook() const
    {
        return _timeToCook;
    }

    std::size_t PizzaOrderHasher::operator()(const PizzaOrder &order) const
    {
        std::size_t seed = 0x50C68423;
        seed ^= (seed << 6) + (seed >> 2) + 0x146C67DE +
            static_cast<std::size_t>(order.size);
        std::hash<std::string> stringHasher;
        seed ^= (seed << 6) + (seed >> 2) + 0x4787A36D +
            stringHasher(order.pizzaName);
        return seed;
    }

    bool operator==(const PizzaOrder &lhs, const PizzaOrder &rhs)
    {
        return lhs.size == rhs.size && lhs.pizzaName == rhs.pizzaName;
    }

    std::istream &operator>>(std::istream &stream, PizzaOrder &pizzaOrder)
    {
        std::string name;
        stream >> name;
        std::ranges::transform(name, name.begin(), tolower);
        pizzaOrder.pizzaName = name;
        if (!PizzaFactory::doesPizzaExists(pizzaOrder.pizzaName))
            stream.setstate(std::ios::badbit);
        if (stream.peek() == ' ')
            stream >> pizzaOrder.size;
        else
            stream.setstate(std::ios::badbit);
        return stream;
    }

    std::ostream &operator<<(std::ostream &stream, const PizzaOrder &pizzaOrder)
    {
        std::string size;

        for (const auto &[fst, snd] : PIZZA_SIZE_FROM_STR)
            if (snd == pizzaOrder.size)
                size = fst;
        return stream << pizzaOrder.pizzaName << " " << size;
    }
} // namespace plazza
