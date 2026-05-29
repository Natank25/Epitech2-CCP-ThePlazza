/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#include "KitchenProcess.hpp"

#include <functional>

#include "Constants.hpp"
#include "Kitchen.hpp"
#include "../Poller.hpp"

namespace plazza {
    KitchenProcess::KitchenProcess(
        size_t id, std::size_t nbCooks, std::chrono::milliseconds refillTime, double multiplier) :
        _id(id),
        _namedPipeName(createTempFileName()),
        _toReception(_namedPipeName + RECEPTION_PIPE_SUFFIX),
        _orders(_namedPipeName + ORDERS_PIPE_SUFFIX),
        _pizzaReady(_namedPipeName + READY_PIZZAS_PIPE_SUFFIX),
        _process(
            kitchenLoop, std::ref(*this), nbCooks, refillTime, multiplier)
    {
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
            PizzaOrder order;
            if (!(process._orders >> order))
                break;
            if (kitchen.isFull()) {
                process._toReception << false;
            } else {
                process._toReception << true;
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
