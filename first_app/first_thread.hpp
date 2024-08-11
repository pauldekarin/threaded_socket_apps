#ifndef FIRST_THREAD_HPP
#define FIRST_THREAD_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <regex>
#include <chrono>
#include <sys/select.h>
#include <memory>

#include "../utilities/buffer.hpp"
#include "../utilities/controller.hpp"
#include "../utilities/logger.hpp"
#include "../utilities/observer.hpp"

#define MAX_SIZE 64

class FirstThread : public Observer{
    std::shared_ptr<Buffer> buffer; 
    std::atomic<bool> is_running {true};

    bool user_input_something();  
    bool validate_user_input(const std::string &user_input);
    void process_user_input(std::string &user_input);

    void sort_user_input(std::string &user_input);
    void replace_even_elements_user_input(std::string &user_input);

    public:

    FirstThread(std::shared_ptr<Buffer> buffer);
    ~FirstThread();

    void exec();
    void stop();
};

#endif