/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#include <chrono>
#include <thread>

#include "../Pizza/PizzaFactory.hpp"
#include "Cook.hpp"
#include "Kitchen.hpp"

namespace plazza {
    void Cook::cookLoop(Kitchen &kitchen, Stock &stock,
        double multiplier,
        const std::function<void(const PizzaOrder &)> &onDone)
    {
        try {
            while (true) {
                PizzaOrder order = kitchen.popOrder();
                Pizza pizza = PizzaFactory::createPizza(order.pizzaName);

                for (const auto &ingredient : pizza.getIngredients())
                    stock.retrieveIngredient(ingredient, 1);
                auto cookingTime = pizza.getTimeToCook() * multiplier;

                std::this_thread::sleep_for(cookingTime);
                if (onDone)
                    onDone(order);
            }
        } catch (const std::runtime_error &) {
        }
    }

} // namespace plazza
