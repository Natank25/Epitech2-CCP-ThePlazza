/*
** EPITECH PROJECT, 2026
** ThePlazza
** File description:
** ${descriptor}
*/

#include "Shell.hpp"

#include <iostream>
#include <sstream>

#include "Constants.hpp"

namespace plazza {
    Shell::Shell(std::vector<std::string> const &args) :
        _cookingMulti(1.0),
        _nbCooks(5),
        _refillTime(1000),
        _exitShell(false),
        _reception(
            _nbCooks, std::chrono::milliseconds(_refillTime), _cookingMulti)
    {
        if (args.size() != 4)
            throw InvalidArgs("Invalid number of arguments.");
        std::istringstream cookingMultSs(args[1]);
        cookingMultSs >> _cookingMulti;
        if (!cookingMultSs || !cookingMultSs.eof())
            throw std::runtime_error("First argument is not a valid double");
        std::istringstream nbCooksSs(args[2]);
        nbCooksSs >> _nbCooks;
        if (!nbCooksSs || !nbCooksSs.eof() || nbCooksSs.str().starts_with("-"))
            throw std::runtime_error(
                "Second argument is not a valid unsigned int");
        std::istringstream refillTimeSs(args[3]);
        refillTimeSs >> _refillTime;
        if (!refillTimeSs || !refillTimeSs.eof() ||
            refillTimeSs.str().starts_with("-"))
            throw std::runtime_error(
                "Third argument is not a valid unsigned int");
        this->_reception = Reception(
            _nbCooks, std::chrono::milliseconds(_refillTime), _cookingMulti);
    }

    void Shell::readUserInput()
    {
        std::string input;

        getline(std::cin, input);
        if (input.empty())
            return;
        if (input == STATUS_COMMAND) {
            this->_reception.status();
        } else {
            try {
                this->_reception.parseLine(input);
            } catch (const InvalidOrderException &e) {
                std::cout << e.what() << std::endl;
            }
            this->_reception.sendOrders();
        }
        std::cout << "> " << std::flush;
    }

    void Shell::handleReadableFd(int readableFd)
    {
        if (readableFd == STDIN_FILENO)
            this->readUserInput();
        else
            this->_reception.handleKitchenResponse(readableFd);
    }

    int Shell::executeShell()
    {
        std::vector<int> kitchensFds = {};
        std::cout << "> " << std::flush;

        while (!std::cin.eof() && !getExitShell()) {
            Poller poller;
            poller.pushBack(STDIN_FILENO);
            for (int kitchensFd : kitchensFds)
                poller.pushBack(kitchensFd);
            poller.poll();
            auto readableFds = poller.getPollResult();
            for (int readableFd : readableFds)
                this->handleReadableFd(readableFd);
            kitchensFds = this->_reception.getPizzasReadyFds();
        }
        return EPI_SUCCESS;
    }

    Shell::InvalidArgs::InvalidArgs(const std::string &msg)
    {
        _msg = msg;
    }

    const char *Shell::InvalidArgs::what() const noexcept
    {
        return _msg.c_str();
    }

    bool Shell::getExitShell() const
    {
        return _exitShell;
    }

    void Shell::exitShell()
    {
        _exitShell = true;
    }

    unsigned int Shell::getRefillTime() const
    {
        return _refillTime;
    }

    unsigned int Shell::getNbCooks() const
    {
        return _nbCooks;
    }

    double Shell::getCookingMulti() const
    {
        return _cookingMulti;
    }
} // namespace plazza
