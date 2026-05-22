/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef TOMATO_HPP
    #define TOMATO_HPP
    #include "IIngredient.hpp"

namespace plazza {
    class Tomato : public IIngredient {
        public:
        [[nodiscard]] std::string getImagePath() const override;
        [[nodiscard]] std::string_view getName() const override;
    };

    constexpr std::string_view TOMATO_PATH = "Assets/Tomato.png";
}

#endif //TOMATO_HPP
