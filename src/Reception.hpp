/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#ifndef RECEPTION_HPP
    #define RECEPTION_HPP

    #include <fstream>
    #include <string>
    #include <unordered_map>

    #include "Kitchen/KitchenProcess.hpp"
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
        Reception(
            std::size_t numCook, std::size_t refillTime, double multiplier);
        void parseLine(const std::string &line);

        void sendOrders();

        void handleKitchenResponse(int fd);

        std::vector<int> getPizzasReadyFds();

    private:
        static std::pair<PizzaOrder, size_t> parseSingleOrder(
            const std::string &orderString);

        static void getPizzaCount(std::istream &stream, size_t &pizzaCount);

        std::unordered_map<PizzaOrder, size_t, PizzaOrderHasher> _orders;
        std::size_t _numCook;
        std::size_t _refillTime;
        double _multiplier;
        std::ofstream _logFile {LOG_FILE};

        static constexpr auto LOG_FILE = "./Plazza.log";
        static constexpr char ORDER_SEPARATOR = ';';
        static constexpr char PIZZA_COUNT_SYMBOL = 'x';

        std::vector<KitchenProcess> _kitchens;

        void sendOrder(decltype(_orders)::value_type &order);
    };
} // namespace plazza
#endif
