/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#include <sstream>
#include <utility>

#include "Reception.hpp"

#include "Pizza/PizzaFactory.hpp"

namespace plazza {
    InvalidOrderException::InvalidOrderException(std::string errorMsg) :
        _errorMsg(std::move(errorMsg))
    {
    }

    const char *InvalidOrderException::what() const noexcept
    {
        return this->_errorMsg.c_str();
    }

    void Reception::parseLine(const std::string &line)
    {
        std::istringstream iss(line);
        std::string order;

        if (line.ends_with(';'))
            throw InvalidOrderException("Last order cannot be empty");
        while (std::getline(iss, order, ORDER_SEPARATOR)) {
            auto [pizzaOrder, pizzaCount] = parseSingleOrder(order);
            this->_orders[pizzaOrder] += pizzaCount;
        }
        for (const auto &[pizzaOrder, count] : this->_orders)
            std::cout << pizzaOrder.pizzaName << pizzaOrder << " x" << count << std::endl;
    }

    void Reception::sendOrders()
    {

    }

    std::pair<PizzaOrder, size_t> Reception::parseSingleOrder(
        const std::string &orderString)
    {
        std::istringstream iss(orderString);
        if (!iss.eof())
            iss >> std::ws;
        if (iss.eof())
            throw InvalidOrderException("Order cannot be empty");
        PizzaOrder order;
        iss >> order;
        if (iss.peek() != ' ')
            throw InvalidOrderException("Expected space character.");
        size_t pizzaCount;
        getPizzaCount(iss, pizzaCount);
        if (!iss || !iss.eof())
            throw InvalidOrderException(
                "The order \"" + orderString + "\" is invalid.");
        return {order, pizzaCount};
    }

    void Reception::getPizzaCount(std::istream &stream, size_t &pizzaCount)
    {
        char multiplierSym;
        stream >> multiplierSym;
        if (multiplierSym != PIZZA_COUNT_SYMBOL)
            stream.setstate(std::ios::badbit);
        else
            stream >> pizzaCount;
    }
}
