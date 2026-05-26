/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#include "KitchenProcess.hpp"

namespace plazza {
    KitchenProcess::KitchenProcess() :
        _namedPipeName(createTempFileName()),
        _toReception(_namedPipeName), _toKitchen(_namedPipeName),
        _process(kitchenLoop, _toReception, _toKitchen)
    {
    }

    int KitchenProcess::kitchenLoop(NamedPipe toReception, NamedPipe toKitchen)
    {
        return 0;
    }

    std::string KitchenProcess::createTempFileName()
    {
        static std::size_t kitchenId = 0;

        std::string kitchenIdStr = std::to_string(kitchenId);
        kitchenId++;
        return DEFAULT_TEMP_NAME + kitchenIdStr;
    }
} // plazza
