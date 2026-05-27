/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#include "KitchenProcess.hpp"

#include <functional>

namespace plazza {
    KitchenProcess::KitchenProcess() :
        _namedPipeName(createTempFileName()),
        _toReception(_namedPipeName + RECEPTION_PIPE_SUFFIX),
        _toKitchen(_namedPipeName + KITCHEN_PIPE_SUFFIX),
        _process(kitchenLoop, std::ref(_toReception), std::ref(_toKitchen))
    {
    }

    int KitchenProcess::kitchenLoop(NamedPipe &toReception, NamedPipe &toKitchen)
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

    NamedPipe &KitchenProcess::getToReception()
    {
        return _toReception;
    }

    NamedPipe &KitchenProcess::getToKitchen()
    {
        return _toKitchen;
    }
} // plazza
