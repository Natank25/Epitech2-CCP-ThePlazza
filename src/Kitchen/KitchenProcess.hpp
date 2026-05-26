/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#ifndef KITCHENPROCESS_HPP
    #define KITCHENPROCESS_HPP
    #include "../IPC/NamedPipe.hpp"
    #include "../IPC/Process.hpp"

namespace plazza {
    class KitchenProcess {
    public:
        KitchenProcess();

        static int kitchenLoop(NamedPipe toReception, NamedPipe toKitchen);
        static std::string createTempFileName();
    private:
        std::string _namedPipeName;
        NamedPipe _toReception;
        NamedPipe _toKitchen;
        Process _process;

        static constexpr auto DEFAULT_TEMP_NAME = "/tmp/PlazzaKitchenNum";
    };
} // plazza

#endif
