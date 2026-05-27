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
    #include "../Pizza/Pizza.hpp"

namespace plazza {
    class KitchenProcess {
    public:
        KitchenProcess(std::size_t nbCooks, int refillTimeMs,
            double multiplier);
        KitchenProcess();

        [[nodiscard]] NamedPipe &getToReception();
        [[nodiscard]] NamedPipe &getToKitchen();

    private:
        static int kitchenLoop(NamedPipe toReception, const NamedPipe& toKitchen,
            std::size_t nbCooks, int refillTimeMs, double multiplier);

        static std::string createTempFileName();

        std::string _namedPipeName;
        NamedPipe _toReception;
        NamedPipe _toKitchen;
        Process _process;

        static constexpr auto DEFAULT_TEMP_NAME = "/tmp/PlazzaKitchenNum";

        static constexpr auto RECEPTION_PIPE_SUFFIX = "ToReception";
        static constexpr auto KITCHEN_PIPE_SUFFIX = "ToKitchen";
    };
} // namespace plazza

#endif
