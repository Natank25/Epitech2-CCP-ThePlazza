/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef INGREDIENT_HPP
    #define INGREDIENT_HPP

namespace plazza {
    struct Ingredient {
        std::string name;
        std::string imagePath;
    };

    static const std::string TOMATO_PATH{"Assets/Tomato.png"};

    static const Ingredient DOUGH = {"dough", std::string("TODO")};
    static const Ingredient TOMATO = {"tomato", std::string(TOMATO_PATH)};
    static const Ingredient GRUYERE = {"gruyere", std::string("TODO")};
    static const Ingredient HAM = {"ham", std::string("TODO")};
    static const Ingredient MUSHROOMS = {"mushrooms", std::string("TODO")};
    static const Ingredient STEAK = {"steak", std::string("TODO")};
    static const Ingredient EGGPLANT = {"eggplant", std::string("TODO")};
    static const Ingredient GOAT_CHEESE = {"goat cheese", std::string("TODO")};
    static const Ingredient CHIEF_LOVE = {"chief love", std::string("TODO")};

}

#endif //INGREDIENT_HPP
