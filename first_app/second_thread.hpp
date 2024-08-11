#ifndef SECOND_THREAD_HPP
#define SECOND_THREAD_HPP

#include <iostream>
#include <numeric>
#include <regex>
#include <cctype>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <memory>

#include "../utilities/buffer.hpp"
#include "../utilities/controller.hpp"
#include "../utilities/logger.hpp"
#include "../utilities/observer.hpp"
#include "../utilities/globals.hpp"

class SecondThread : public Observer{
    public:

    SecondThread(std::shared_ptr<Buffer> buffer);
    ~SecondThread();
    
    void exec();

    private:
    std::shared_ptr<Buffer> buffer;
    std::atomic<bool> is_running {true};

    int sum_digits(const std::string &user_input);
    void send_to_second_app(int sum);

    void stop();
};

#endif