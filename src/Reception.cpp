/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#include "Reception.hpp"

#include <fstream>
#include <sstream>
#include <utility>

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

    Reception::Reception(
        std::size_t numCook, std::size_t refillTime, double multiplier) :
        _numCook(numCook), _refillTime(refillTime), _multiplier(multiplier)
    {
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
    }

    void Reception::sendOrders()
    {
        for (auto &order : this->_orders) {
            while (order.second != 0)
                this->sendOrder(order);
        }
    }

    void Reception::handleKitchenResponse(int fd)
    {
        auto kitchenReady =
            std::ranges::find(this->_kitchens, fd, [](const auto &kitchen) {
                return kitchen.getPizzaReady().getReadFd();
            });
        if (kitchenReady == this->_kitchens.end())
            return;
        PizzaOrder order;
        kitchenReady->getPizzaReady() >> order;
        this->_logFile << "Order: " << order << " finished!" << std::endl;
        for (; kitchenReady->getPizzaReady().isReadable();
            kitchenReady->getPizzaReady() >> order)
            this->_logFile << "Order: " << order << " finished!" << std::endl;
    }

    std::vector<int> Reception::getPizzasReadyFds()
    {
        std::vector<int> ordersFd = {};

        ordersFd.reserve(this->_kitchens.size());
        for (auto &kitchen : this->_kitchens) {
            auto &readyPizza = kitchen.getPizzaReady();
            readyPizza.openRead();
            ordersFd.emplace_back(readyPizza.getReadFd());
        }
        return ordersFd;
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
        if (!iss)
            throw InvalidOrderException("The name or the size is invalid.");
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

    void Reception::sendOrder(decltype(_orders)::value_type &order)
    {
        for (auto &kitchen : this->_kitchens) {
            kitchen.getOrders() << order.first;
            bool tookOrder = false;
            if (!(kitchen.getToReception() >> tookOrder) || !tookOrder)
                continue;
            order.second--;
            return;
        }
        auto &newKitchen = this->_kitchens.emplace_back(
            this->_numCook, this->_refillTime, this->_multiplier);
        newKitchen.getOrders() << order.first;
        bool tookOrder = false;
        if (!(newKitchen.getToReception() >> tookOrder) || !tookOrder)
            throw std::runtime_error("New kitchen did not accept order");
        order.second--;
    }
} // namespace plazza
