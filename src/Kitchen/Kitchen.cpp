/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#include "Kitchen.hpp"

#include <iomanip>

#include "Cook.hpp"
#include "../Pizza/PizzaFactory.hpp"

namespace plazza {

    Kitchen::Kitchen(std::chrono::milliseconds refillTimeMs, double multiplier, std::size_t nbCooks) :
        _refillTime(refillTimeMs),
        _multiplier(multiplier),
        _running(true),
        _estimatedLastActivity(
            std::chrono::steady_clock::now() + INACTIVITY_CLOSE_TIME)
    {
        for (std::size_t i = 0; i < nbCooks; ++i)
            _cooks.emplace_back();
    }

    Kitchen::~Kitchen()
    {
        shutdown();
    }

    void Kitchen::start()
    {
        _threads.emplace_back([this] {
            stockRefillLoop();
        });
        _threads.emplace_back([this] {
            inactivityCheckLoop();
        });
        for (auto &_ : this->_cooks)
            _threads.emplace_back([this] {
                Cook::cookLoop(*this, _stock, _multiplier, _onPizzaDone);
            });
    }

    void Kitchen::updatedEstimatedLastActivity()
    {
        auto estimatedLastActivity = std::chrono::steady_clock::now() +
                INACTIVITY_CLOSE_TIME;
        this->_estimatedLastActivity = std::max(
            this->_estimatedLastActivity.load(),
            estimatedLastActivity);
    }

    void Kitchen::enqueue(const PizzaOrder &order)
    {
        _queue.push(order);
    }

    PizzaOrder Kitchen::popOrder()
    {
        return this->_queue.pop();
    }

    bool Kitchen::isFull() const
    {
        return _queue.size() >= _cooks.size();
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
            if (t.joinable())
                t.join();
    }

    void Kitchen::stockRefillLoop()
    {
        while (_running) {
            std::this_thread::sleep_for(_refillTime);
            _stock.refillIngredients();
        }
    }

    void Kitchen::inactivityCheckLoop()
    {
        while (_running) {
            auto activityTimeout = this->_estimatedLastActivity.load() -
                std::chrono::steady_clock::now();
            std::this_thread::sleep_for(activityTimeout);
            if (std::chrono::steady_clock::now() < this->_estimatedLastActivity.
                load())
                continue;
            if (_queue.empty()) {
                _running = false;
                _queue.stop();
            }
        }
    }

} // namespace plazza
