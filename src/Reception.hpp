/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#ifndef RECEPTION_HPP
    #define RECEPTION_HPP

    #include <string>
    #include <unordered_map>

    #include "Pizza/Pizza.hpp"

namespace plazza {
    class InvalidOrderException : std::exception {
    public:
        explicit InvalidOrderException(std::string errorMsg);

        [[nodiscard]] const char *what() const noexcept override;
    private:
        std::string _errorMsg;
    };

    class Reception {
    public:
        void parseLine(const std::string &line);

        static std::pair<PizzaOrder, size_t> parseSingleOrder(const std::string &orderString);
    private:
        static void getPizzaCount(std::istream &stream, size_t &pizzaCount);

        std::unordered_map<PizzaOrder, size_t, PizzaOrderHasher> _orders;
        static constexpr char ORDER_SEPARATOR = ';';
        static constexpr char PIZZA_COUNT_SYMBOL = 'x';
    };
}
#endif