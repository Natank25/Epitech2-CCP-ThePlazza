/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#include "Kitchen.hpp"
#include "Cook.hpp"

namespace plazza {

    Kitchen::Kitchen(int refillTimeMs, double multiplier, std::size_t nbCooks)
        : _refillTimeMs(refillTimeMs), _multiplier(multiplier),
          _running(true), _lastActivity(std::chrono::steady_clock::now())
    {
        std::cout << "Created kitchen with " << nbCooks << " cooks" << std::endl;
        for (std::size_t i = 0; i < nbCooks; ++i)
            _cooks.emplace_back();
    }

    Kitchen::~Kitchen()
    {
        shutdown();
    }

    void Kitchen::start()
    {
        _threads.emplace_back([this]{ stockRefillLoop(); });
        _threads.emplace_back([this]{ inactivityCheckLoop(); });
        for (auto &cook : _cooks)
            _threads.emplace_back([&cook, this]{
                cook.cookLoop(_queue, _stock, _multiplier, _onPizzaDone);
            });
    }

    void Kitchen::enqueue(const PizzaOrder &order)
    {
        _lastActivity = std::chrono::steady_clock::now();
        _queue.push(order);
    }

    bool Kitchen::isFull() const
    {
        return _queue.size() >= 2 * _cooks.size();
    }

    bool Kitchen::isRunning() const
    {
        return _running;
    }

    void Kitchen::setOnPizzaDone(std::function<void(const PizzaOrder &)> cb)
    {
        _onPizzaDone = std::move(cb);
    }

    void Kitchen::shutdown()
    {
        _running = false;
        _queue.stop();
        for (auto &t : _threads)
            if (t.joinable()) t.join();
    }

    void Kitchen::stockRefillLoop()
    {
        while (_running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(_refillTimeMs));
            _stock.refillIngredients();
        }
    }

    void Kitchen::inactivityCheckLoop()
    {
        while (_running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(CHECK_ACTIVITY_INTERVAL_MS));
            auto idle = std::chrono::steady_clock::now() - _lastActivity.load();
            if (_queue.empty() && idle >= std::chrono::seconds(INACTIVITY_CLOSE_TIME_S)) {
                _running = false;
                _queue.stop();
            }
        }
    }

} // namespace plazza