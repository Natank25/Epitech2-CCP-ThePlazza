/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** DESCRIPTION
*/

#ifndef KITCHENPROCESS_HPP
    #define KITCHENPROCESS_HPP
    #include <bits/chrono.h>

    #include "../IPC/NamedPipe.hpp"
    #include "../IPC/Process.hpp"

namespace plazza {
    class KitchenProcess {
    public:
        KitchenProcess(size_t id,
            std::size_t nbCooks, std::chrono::milliseconds refillTime, double multiplier);

        KitchenProcess(const KitchenProcess &) = delete;
        KitchenProcess &operator=(const KitchenProcess &) = delete;

        KitchenProcess(KitchenProcess &&) noexcept = default;
        KitchenProcess &operator=(KitchenProcess &&) noexcept = default;

        [[nodiscard]] NamedPipe &getToReception();
        [[nodiscard]] NamedPipe &getOrders();
        [[nodiscard]] NamedPipe &getPizzaReady();

        [[nodiscard]] const NamedPipe &getToReception() const;
        [[nodiscard]] const NamedPipe &getOrders() const;
        [[nodiscard]] const NamedPipe &getPizzaReady() const;
        [[nodiscard]] const std::size_t &getId() const;

        static constexpr auto ORDER_DONE_CMD = "ORDER";
        static constexpr auto KITCHEN_CLOSE_CMD = "CLOSED";

    private:
        static int kitchenLoop(KitchenProcess &process, size_t nbCooks,
            std::chrono::milliseconds refillTime, double multiplier);

        [[nodiscard]] std::string createTempFileName() const;

        std::string _namedPipeName;
        NamedPipe _toReception;
        NamedPipe _orders;
        NamedPipe _pizzaReady;
        Process _process;
        std::size_t _id;

        static constexpr auto DEFAULT_TEMP_NAME = "/tmp/PlazzaKitchenNum";

        static constexpr auto RECEPTION_PIPE_SUFFIX = "-reception";
        static constexpr auto ORDERS_PIPE_SUFFIX = "-orders";
        static constexpr auto READY_PIZZAS_PIPE_SUFFIX = "-pizzas-ready";
    };
} // namespace plazza

#endif
