#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <thread>
#include <chrono>
#include "../utilities/logger.hpp"
#include "../utilities/observer.hpp"
#include "../utilities/globals.hpp"

class Listener : public Observer{
    int sockfd;
    struct sockaddr_in sock_in;

    bool read_data(std::string &data);
    bool is_running {true};

    bool create_socket();
    bool bind_socket();
public:
    Listener();
    ~Listener();

    std::string listen();
    void stop();
};

#endif