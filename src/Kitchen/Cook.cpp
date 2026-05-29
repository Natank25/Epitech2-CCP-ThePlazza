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
    Cook::Cook(std::size_t id) :
        _occupied(false), _id(id)
    {
    }

    void Cook::cookLoop(Kitchen &kitchen, Stock &stock, double multiplier,
        const std::function<void(const PizzaOrder &)> &onDone)
    {
        try {
            while (true) {
                this->_occupied = false;
                PizzaOrder order = kitchen.popOrder();
                this->_occupied = true;
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

    std::size_t Cook::getId() const
    {
        return this->_id;
    }

    JSON::JSON Cook::getStatus() const
    {
        JSON::JSON status = JSON::JSON::object();

        status.set("occupied", this->_occupied);
        return status;
    }

} // namespace plazza
