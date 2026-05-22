/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#include "Kitchen.hpp"

namespace plazza {
    Kitchen::Kitchen(std::size_t const _numberCooks) : _timeSinceLastRefill(0)
    {
        _cooks.reserve(_numberCooks);
        for (int i = 0; i < _cooks.capacity(); ++i)
            _cooks.insert(_cooks.begin(), Cook());
    }

    void Kitchen::refill(double deltaTime)
    {
        if (_timeSinceLastRefill + deltaTime <= 1)
            _stock.refillIngredients();
    }
}
