/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#include "Reception.hpp"

#include <chrono>
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

    Reception::Reception(std::size_t numCook,
        std::chrono::milliseconds refillTime, double multiplier) :
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

    void Reception::handleKitchenCommand(
        const std::ranges::borrowed_iterator_t<std::vector<KitchenProcess> &>
            &kitchenReady,
        const std::string &data)
    {
        std::istringstream iss(data);
        std::string command;
        iss >> command;
        if (!iss.eof())
            iss >> std::ws;
        if (KITCHEN_COMMANDS_FNS.contains(command))
            (this->*KITCHEN_COMMANDS_FNS.at(command))(kitchenReady, iss);
    }

    void Reception::handleKitchenResponse(int fd)
    {
        auto kitchenReady =
            std::ranges::find(this->_kitchens, fd, [](const auto &kitchen) {
                return kitchen.getPizzaReady().getReadFd();
            });
        if (kitchenReady == this->_kitchens.end())
            return;
        std::string fullLine = kitchenReady->getPizzaReady().getLine();
        this->handleKitchenCommand(kitchenReady, fullLine);
        for (; kitchenReady->getPizzaReady().isReadable();
            fullLine = kitchenReady->getPizzaReady().getLine())
            this->handleKitchenCommand(kitchenReady, fullLine);
        ;
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

    std::ofstream &Reception::startLog()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                      now.time_since_epoch()) %
            1000;

        this->_logFile << "["
                       << std::put_time(std::localtime(&now_c), "%H:%M:%S")
                       << "." << std::setfill('0') << std::setw(3) << ms.count()
                       << "] ";
        return this->_logFile;
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
        auto &newKitchen = this->addNewKitchen();
        newKitchen.getOrders() << order.first;
        bool tookOrder = false;
        if (!(newKitchen.getToReception() >> tookOrder) || !tookOrder)
            throw std::runtime_error("New kitchen did not accept order");
        order.second--;
    }

    KitchenProcess &Reception::addNewKitchen()
    {
        KitchenProcess &newKitchen =
            this->_kitchens.emplace_back(this->_nextKitchenId,
                this->_numCook,
                this->_refillTime,
                this->_multiplier);
        this->startLog() << "Opening new kitchen with id: "
                         << this->_nextKitchenId << std::endl;
        this->_nextKitchenId++;
        return newKitchen;
    }

    void Reception::handleFinishedOrderCmd(
        KitchenProcessIterator kitchen, std::istringstream &line)
    {
        PizzaOrder order;
        line >> order;
        this->startLog() << "Kitchen " << kitchen->getId() << " finished order "
                         << order << "." << std::endl;
    }

    void Reception::handleClosedKitchenCmd(
        KitchenProcessIterator kitchen, std::istringstream &)
    {
        this->startLog() << "Kitchen " << kitchen->getId()
                         << " closed for good!" << std::endl;
        this->_kitchens.erase(kitchen);
    }

    const std::unordered_map<std::string,
        void (Reception::*)(
            Reception::KitchenProcessIterator, std::istringstream &)>
        Reception::KITCHEN_COMMANDS_FNS = {
            {KitchenProcess::ORDER_DONE_CMD,
                &Reception::handleFinishedOrderCmd},
            {KitchenProcess::KITCHEN_CLOSE_CMD,
                &Reception::handleClosedKitchenCmd},
    };
} // namespace plazza
