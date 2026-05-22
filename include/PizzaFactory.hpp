/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef PIZZAFACTORY_HPP
    #define PIZZAFACTORY_HPP
#include <functional>
#include <unordered_map>

#include "Pizza.hpp"

namespace plazza {
    class PizzaFactory {
    public:
        static Pizza createPizza(std::string name);
    private:
        static std::unordered_map<std::string, std::function<Pizza>> _factories;
    };
}

#endif //PIZZAFACTORY_HPP