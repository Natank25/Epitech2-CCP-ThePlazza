/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef IINGREDIENTS_HPP
    #define IINGREDIENTS_HPP
#include <string>

namespace plazza {
    class IIngredient {
    public:
        virtual ~IIngredient() = default;

        virtual std::string getImagePath() const = 0;
        virtual std::string getName() const = 0;
    };
}

#endif //IINGREDIENTS_HPP
