#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <string>
#include <mutex>
#include <condition_variable>
#include <atomic>


#include "controller.hpp"
#include "logger.hpp"
#include "observer.hpp"

class Buffer : public Observer{
    public:
    Buffer();
    ~Buffer();

    void stop();

    void set(const std::string &user_input);
    std::string get();


    private:
    std::string buffer;
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> is_empty;
    std::atomic<bool> is_running;
};

#endif