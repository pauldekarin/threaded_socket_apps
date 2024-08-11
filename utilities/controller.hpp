#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <atomic>
#include <vector>
#include <csignal>
#include <memory>

#include "logger.hpp"
#include "observer.hpp"

class StateController{
    std::atomic<bool> is_running{true};
    std::vector<std::shared_ptr<Observer>> observers;


    public:
    StateController();
    ~StateController();

    void insert_observer(std::shared_ptr<Observer> observer);
    void stop_all_observers();
    static void catch_sigint(int signum);

    inline static StateController *instance;
};


#endif