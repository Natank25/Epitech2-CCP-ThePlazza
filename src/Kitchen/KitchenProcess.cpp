/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#include "KitchenProcess.hpp"
#include "Kitchen.hpp"
#include "Constants.hpp"

#include <functional>

namespace plazza {
    KitchenProcess::KitchenProcess(std::size_t nbCooks, int refillTimeMs,
        double multiplier) :
        _namedPipeName(createTempFileName()),
        _toReception(_namedPipeName + RECEPTION_PIPE_SUFFIX),
        _orders(_namedPipeName + ORDERS_PIPE_SUFFIX),
        _pizzaReady(_namedPipeName + READY_PIZZAS_PIPE_SUFFIX),
        _process(kitchenLoop, std::ref(*this), nbCooks, refillTimeMs, multiplier)
    {
    }

    int KitchenProcess::kitchenLoop(KitchenProcess &process,
        size_t nbCooks, int refillTimeMs, double multiplier)
    {
        Kitchen kitchen(refillTimeMs, multiplier, nbCooks);

        kitchen.setOnPizzaDone([&process](const PizzaOrder &order) {
            process._pizzaReady << order.pizzaName;
        });

        kitchen.start();

        while (kitchen.isRunning()) {
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
        kitchen.shutdown();
        return EPI_SUCCESS;
    }

    std::string KitchenProcess::createTempFileName()
    {
        static std::size_t kitchenId = 0;

        std::string kitchenIdStr = std::to_string(kitchenId);
        kitchenId++;
        return DEFAULT_TEMP_NAME + kitchenIdStr;
    }

    NamedPipe &KitchenProcess::getToReception()
    {
        return _toReception;
    }

    NamedPipe &KitchenProcess::getOrders()
    {
        return _orders;
    }
} // namespace plazza
