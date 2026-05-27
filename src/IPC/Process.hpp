/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** Process
*/

#ifndef PROCESS_HPP
    #define PROCESS_HPP
    #include <cerrno>
    #include <cstdlib>
    #include <exception>
    #include <stdexcept>
    #include <unistd.h>

namespace plazza {
    class Process {
    public:
        Process(const Process &) = delete;
        Process &operator=(const Process &) = delete;

        Process(Process &&other) noexcept;
        Process &operator=(Process &&other) noexcept;

        class FailedForkException : std::exception {
        public:
            explicit FailedForkException(int errnoValue = errno);

            [[nodiscard]] const char *what() const noexcept override;

        private:
            int _errnoValue;
        };

        template<typename Callable, typename... Args>
            requires std::is_invocable_v<std::decay_t<Callable>,
                         std::decay_t<Args>...>
                     && std::is_convertible_v<std::invoke_result_t<
                         std::decay_t<Callable>, std::decay_t<Args>...>, int>
        explicit Process(Callable &&f, Args &&... args) :
            _pid(fork())
        {
            if (_pid == -1)
                throw FailedForkException(errno);
            if (_pid == 0) {
                int ret = std::forward<
                    Callable>(f)(std::forward<Args>(args)...);
                std::exit(ret);
            }
        }

        explicit Process();

        [[nodiscard]] int getPID() const
        {
            return this->_pid;
        }

        int wait(int options = 0);

        [[nodiscard]] int getExitStatus() const;

    private:
        int _pid;
        int _exitStatus{DEFAULT_EXIT_STATUS};

        static constexpr int DEFAULT_EXIT_STATUS = -1;
    };
} // ThePlazza

#endif
