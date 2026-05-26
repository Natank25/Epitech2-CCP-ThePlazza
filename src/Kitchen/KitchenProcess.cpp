/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#include "KitchenProcess.hpp"
#include "Kitchen.hpp"
#include "Constants.hpp"

namespace plazza {
    KitchenProcess::KitchenProcess(std::size_t nbCooks, int refillTimeMs,
        double multiplier)
        : _namedPipeName(createTempFileName()),
        _toReception(_namedPipeName),
        _toKitchen(_namedPipeName),
        _process(kitchenLoop, _toReception, _toKitchen, nbCooks, refillTimeMs,
            multiplier)
    {
    }

    int KitchenProcess::kitchenLoop(NamedPipe toReception, NamedPipe toKitchen,
        std::size_t nbCooks, int refillTimeMs, double multiplier)
    {
        Kitchen kitchen(refillTimeMs, multiplier, nbCooks);

        kitchen.setOnPizzaDone([&toReception](const PizzaOrder &order) {
            auto os = toReception.getOutputStream();
            os << order.pizzaName;
        });

        kitchen.start();

        while (kitchen.isRunning()) {
            PizzaOrder order;
            auto is = toKitchen.getInputStream();

            if (!(is >> order))
                break;
            auto os = toReception.getOutputStream();
            if (kitchen.isFull()) {
                os << "KO";
            } else {
                os << "OK";
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
} // namespace plazza
