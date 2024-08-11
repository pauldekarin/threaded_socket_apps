#include"../listener.hpp"

Listener::Listener(){

}
Listener::~Listener(){
    this->stop();
}

void Listener::stop(){
    if(!this->is_running) return;
    this->is_running = false;
    close(this->sockfd);
}

bool Listener::create_socket(){
    if((this->sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        return false;
    }
    int opt = 1;
    if(setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){

        return false;
    }
    return true;
}
bool Listener::bind_socket(){
    std::memset(&sock_in, 0, sizeof(sock_in));

    sock_in.sin_addr.s_addr = inet_addr("127.0.0.1");
    sock_in.sin_family = AF_INET;
    sock_in.sin_port = htons(PORT);
    
    while(bind(sockfd, (struct sockaddr*)&sock_in, sizeof(sock_in)) < 0 && this->is_running){
        close(this->sockfd);
        if(errno == EADDRINUSE){
            logger::cout("LISTENER", "port in use, wait it to be freed or change PORT in file '/utilities/globals.hpp'");
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            if(!this->create_socket()){
                return false;
            }
        }else{
            return false;
        }
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

    data.assign(buffer, sl);

    return true;
}
std::string Listener::listen(){
    std::string data{""};
    
    if(!this->create_socket()){
        logger::cout("LISTENER","error create_socket()");
        return data;
    };
    if(!this->bind_socket()){
        logger::cout("LISTENER","error create_socket()");
        return data;
    }      


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

    close(this->sockfd);

    return data;
}