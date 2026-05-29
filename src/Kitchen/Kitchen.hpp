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
    #include "Stock.hpp"

namespace plazza {
    class Kitchen {
    public:
        Kitchen(int refillTime, double multiplier, std::size_t nbCooks);

        void shutdown();
        void start();

        void enqueue(const PizzaOrder &order);

        bool isFull() const;
        bool isRunning() const;

        void setOnPizzaDone(std::function<void(const PizzaOrder &)> cb);
        void stockRefillLoop();
        void inactivityCheckLoop();

        ~Kitchen();

    private:
        static constexpr int CHECK_ACTIVITY_INTERVAL_MS = 500;
        static constexpr int INACTIVITY_CLOSE_TIME_S = 5;

        int _refillTimeMs;
        double _multiplier;
        std::atomic<bool> _running;
        std::atomic<std::chrono::steady_clock::time_point> _lastActivity;

        Stock _stock;
        SafeQueue<PizzaOrder> _queue;
        std::vector<Cook> _cooks;
        std::vector<std::thread> _threads;

        std::function<void(const PizzaOrder &)> _onPizzaDone;
    };
} // namespace plazza

#endif // KITCHEN_HPP
