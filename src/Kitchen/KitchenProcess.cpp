/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#include "KitchenProcess.hpp"

#include <functional>

#include "../Poller.hpp"
#include "Constants.hpp"
#include "Kitchen.hpp"

namespace plazza {
    KitchenProcess::KitchenProcess(size_t id, std::size_t nbCooks,
        std::chrono::milliseconds refillTime, double multiplier) :
        _id(id),
        _namedPipeName(createTempFileName()),
        _toReception(_namedPipeName + RECEPTION_PIPE_SUFFIX),
        _orders(_namedPipeName + ORDERS_PIPE_SUFFIX),
        _pizzaReady(_namedPipeName + READY_PIZZAS_PIPE_SUFFIX),
        _process(kitchenLoop, std::ref(*this), nbCooks, refillTime, multiplier)
    {
    }

    JSON::JSON KitchenProcess::getStatus()
    {
        this->getOrders() << KITCHEN_STATUS_CMD;

        std::string line = this->getToReception().getLine();
        std::istringstream iss(line);
        return *JSON::JSON::parseStream(iss);
    }

    NamedPipe &KitchenProcess::getToReception()
    {
        return this->_toReception;
    }

    NamedPipe &KitchenProcess::getOrders()
    {
        return this->_orders;
    }

    NamedPipe &KitchenProcess::getPizzaReady()
    {
        return this->_pizzaReady;
    }

    const NamedPipe &KitchenProcess::getToReception() const
    {
        return this->_toReception;
    }

    const NamedPipe &KitchenProcess::getOrders() const
    {
        return this->_orders;
    }

    const NamedPipe &KitchenProcess::getPizzaReady() const
    {
        return this->_pizzaReady;
    }

    const std::size_t &KitchenProcess::getId() const
    {
        return this->_id;
    }

    int KitchenProcess::kitchenLoop(KitchenProcess &process, size_t nbCooks,
        std::chrono::milliseconds refillTime, double multiplier)
    {
        Kitchen kitchen(refillTime, multiplier, nbCooks);

        kitchen.setOnPizzaDone([&process, &kitchen](const PizzaOrder &order) {
            std::ostringstream data;
            data << ORDER_DONE_CMD << " " << order;
            process._pizzaReady << data.str();
            kitchen.updatedEstimatedLastActivity();
        });

        kitchen.start();
        Poller poller;
        process.getOrders().openRead();
        poller.pushBack(process.getOrders().getReadFd());

        while (kitchen.isRunning()) {
            if (poller.poll(0) == 0)
                continue;
            std::string line = process._orders.getLine();
            if (line == KITCHEN_STATUS_CMD) {
                process.getToReception()
                    << kitchen.getStatus().toCompactString();
                continue;
            }
            std::istringstream iss(line);
            PizzaOrder order;
            if (!(iss >> order))
                break;
            if (kitchen.isFull()) {
                process.getToReception() << false;
            } else {
                process.getToReception() << true;
                kitchen.enqueue(order);
            }
        }
        process.getPizzaReady() << KITCHEN_CLOSE_CMD;
        kitchen.shutdown();
        return EPI_SUCCESS;
    }

    std::string KitchenProcess::createTempFileName() const
    {
        std::string kitchenIdStr = std::to_string(this->_id);
        return DEFAULT_TEMP_NAME + kitchenIdStr;
    }
} // namespace plazza
