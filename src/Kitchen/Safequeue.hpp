/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#ifndef SAFEQUEUE_HPP
    #define SAFEQUEUE_HPP
    #include <condition_variable>
    #include <mutex>
    #include <queue>
    #include <stdexcept>

namespace plazza {
    template<typename T>
    class SafeQueue {
    public:
        void push(T item)
        {
            {
                std::unique_lock lock(_mutex);
                _queue.push(std::move(item));
            }
            _itemAvailable.notify_one();
        }

        T pop()
        {
            std::unique_lock lock(_mutex);
            _itemAvailable.wait(
                lock, [this] { return !_queue.empty() || _stop; });
            if (_stop && _queue.empty())
                throw std::runtime_error("SafeQueue stopped");
            T item = std::move(_queue.front());
            _queue.pop();
            return item;
        }

        void stop()
        {
            {
                std::unique_lock lock(_mutex);
                _stop = true;
            }
            _itemAvailable.notify_all();
        }

        std::size_t size() const
        {
            std::unique_lock lock(_mutex);
            return _queue.size();
        }

        bool empty() const
        {
            std::unique_lock lock(_mutex);
            return _queue.empty();
        }

    private:
        std::queue<T> _queue;
        mutable std::mutex _mutex;
        std::condition_variable _itemAvailable;
        bool _stop = false;
    };
} // namespace plazza

#endif
