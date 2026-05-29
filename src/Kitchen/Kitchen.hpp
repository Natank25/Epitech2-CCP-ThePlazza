/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef KITCHEN_HPP
    #define KITCHEN_HPP
    #include <functional>
    #include <queue>

    #include "../Pizza/Pizza.hpp"
    #include "Cook.hpp"
    #include "Json.hpp"
    #include "Stock.hpp"
    #include "Safequeue.hpp"

namespace plazza {
    class Kitchen {
    public:
        Kitchen(std::chrono::milliseconds refillTime, double multiplier,
            std::size_t nbCooks);

        void shutdown();

        void start();

        void updatedEstimatedLastActivity(
        );

        void enqueue(const PizzaOrder &order);

        PizzaOrder popOrder();

        bool isFull() const;

        bool isRunning() const;

        void setOnPizzaDone(std::function<void(const PizzaOrder &)> cb);

        void stockRefillLoop();

        void inactivityCheckLoop();

        ~Kitchen();

        JSON::JSON getCooksStatus() const;

        JSON::JSON getStatus() const;

    private:
        static constexpr int CHECK_ACTIVITY_INTERVAL_MS = 500;
        static constexpr auto INACTIVITY_CLOSE_TIME = std::chrono::seconds(5);

        std::chrono::milliseconds _refillTime;
        double _multiplier;
        std::atomic<bool> _running;
        std::atomic<std::chrono::steady_clock::time_point>
        _estimatedLastActivity;

        Stock _stock;
        SafeQueue<PizzaOrder> _queue;
        std::vector<Cook> _cooks;
        std::vector<std::thread> _threads;

        std::function<void(const PizzaOrder &)> _onPizzaDone;
    };
} // namespace plazza

#endif // KITCHEN_HPP
