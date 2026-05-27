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
        KitchenProcess(std::size_t nbCooks, int refillTimeMs,
            double multiplier);

        [[nodiscard]] NamedPipe &getToReception();
        [[nodiscard]] NamedPipe &getOrders();

    private:
        static int kitchenLoop(KitchenProcess process,
            size_t nbCooks, int refillTimeMs, double multiplier);

        static std::string createTempFileName();

        std::string _namedPipeName;
        NamedPipe _toReception;
        NamedPipe _orders;
        NamedPipe _pizzaReady;
        Process _process;

        static constexpr auto DEFAULT_TEMP_NAME = "/tmp/PlazzaKitchenNum";

        static constexpr auto RECEPTION_PIPE_SUFFIX = "-reception";
        static constexpr auto ORDERS_PIPE_SUFFIX = "-orders";
        static constexpr auto READY_PIZZAS_PIPE_SUFFIX = "-pizzas-ready";
    };
} // namespace plazza

#endif
