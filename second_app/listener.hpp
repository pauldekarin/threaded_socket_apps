#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <string>

#include "../utilities/logger.hpp"
#include "../utilities/observer.hpp"

#define BUFFER_SIZE 1024

class Listener : public Observer{
    int sockfd;
    struct sockaddr_in sock_in;
    bool read_data(std::string &data);
    bool is_running {true};
public:
    Listener();
    ~Listener();

    std::string listen();
    bool bind_socket();
    void stop();
};

#endif