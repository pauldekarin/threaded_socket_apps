#include"../listener.hpp"

Listener::Listener(){
    if((this->sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        logger::cout("LISTENER","socket() error");
        return;
    }
}
Listener::~Listener(){
    this->stop();
}

void Listener::stop(){
    if(!this->is_running) return;
    this->is_running = false;
}

bool Listener::bind_socket(){
    sock_in.sin_addr.s_addr = INADDR_ANY;
    sock_in.sin_family = AF_INET;
    sock_in.sin_port = htons(8080);
    
    if(bind(sockfd, (struct sockaddr*)&sock_in, sizeof(sock_in)) < 0){
        logger::cout("LISTENER","bind() error");
        return false;
    }
    return true;
}

bool Listener::read_data(std::string &data){
    char buffer[BUFFER_SIZE];

    socklen_t addr_len = sizeof(this->sock_in);
    ssize_t sl = recvfrom(this->sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&sock_in, &addr_len);

    if(sl < 0){
        return false;
    }

    data.assign(buffer);

    return true;
}
std::string Listener::listen(){
    std::string data{""};

    if(this->sockfd < 0){
        logger::cout("LISTENER","can't listen() without socket");
    }else{
        fd_set fds;
        struct timeval tm;


        while(this->is_running){
            tm.tv_sec = 0;
            tm.tv_usec = 1000;

            FD_ZERO(&fds);
            FD_SET(sockfd, &fds);

            int s_result = select(sockfd + 1, &fds, nullptr, nullptr, &tm);
            if(s_result < 0){
                logger::cout("LISTENER","select() error");
            }else if(s_result == 0){
                continue; 
            }else {
                logger::cout("LISTENER","catched message from APPLICATION №1");
                read_data(data);
                break;
            }
        }
    }

    return data;
}