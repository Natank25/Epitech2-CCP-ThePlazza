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

    static const std::string TOMATO_PATH{"assets/Tomato.png"};
    static const std::string CHEESE_PATH{"assets/Cheese.png"};
    static const std::string DOUGH_PATH{"assets/Dough.png"};
    static const std::string GRUYERE_PATH{"assets/Cheese.png"};
    static const std::string HAM_PATH{"assets/Ham.png"};
    static const std::string MUSHROOM_PATH{"assets/Mushrooms.png"};
    static const std::string STEAK_PATH{"assets/Steak.png"};
    static const std::string EGGPLANT_PATH{"assets/Eggplant.png"};
    static const std::string GOAT_CHEESE_PATH{"assets/GoatCheese.png"};

    static const Ingredient DOUGH = {"dough", TOMATO_PATH};
    static const Ingredient TOMATO = {"tomato", TOMATO_PATH};
    static const Ingredient GRUYERE = {"gruyere", GRUYERE_PATH};
    static const Ingredient HAM = {"ham", HAM_PATH};
    static const Ingredient MUSHROOMS = {"mushrooms", MUSHROOM_PATH};
    static const Ingredient STEAK = {"steak", STEAK_PATH};
    static const Ingredient EGGPLANT = {"eggplant", EGGPLANT_PATH};
    static const Ingredient GOAT_CHEESE = {"goat cheese", GOAT_CHEESE_PATH};
    static const Ingredient CHIEF_LOVE = {"chief love", "TODO"};

}

#endif //INGREDIENT_HPP
