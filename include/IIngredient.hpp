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

        [[nodiscard]] virtual std::string getImagePath() const = 0;
        [[nodiscard]] virtual std::string_view getName() const = 0;
    };
}

#endif //IINGREDIENTS_HPP
