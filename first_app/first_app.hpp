#ifndef FIRST_APP_H
#define FIRST_APP_H

#include <thread>
#include <mutex>
#include <chrono>

#include "first_thread.hpp"
#include "second_thread.hpp"
#include "../utilities/logger.hpp"
#include "../utilities/observer.hpp"

class FirstApp{
    std::thread first_thread;
    std::thread second_thread;
    
    std::shared_ptr<Buffer> buffer;
    std::shared_ptr<StateController> controller;

    std::atomic<bool> is_running {true};

    public:

    FirstApp();
    ~FirstApp();

    void prepare();
    void exec();

    void stop();
};

#endif