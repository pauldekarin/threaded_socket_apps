#ifndef SECOND_APP_HPP
#define SECOND_APP_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

#include <iostream>
#include <string>
#include <unistd.h>

#include "../utilities/controller.hpp"
#include "../utilities/observer.hpp"
#include "../utilities/logger.hpp"
#include "listener.hpp"
#include "writer.hpp"

#define BUFFER_SIZE 1024

class SecondApp : public Observer, public std::enable_shared_from_this<SecondApp>{
    std::shared_ptr<Listener> listener;
    StateController controller;
    Writer writer;

    bool is_running = true;

    public:
    SecondApp(); 
    ~SecondApp() = default; 
    
    void init();
    void exec();
    void stop();
};

#endif