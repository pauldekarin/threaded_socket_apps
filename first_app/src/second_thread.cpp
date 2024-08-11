#include "../second_thread.hpp"

SecondThread::SecondThread(std::shared_ptr<Buffer> buffer):buffer(buffer){

}
SecondThread::~SecondThread(){

}

void SecondThread::exec(){
    logger::cout("=== THREAD №2 run ===");
    while(true){
        logger::cout("=== THREAD №2 waiting user input ===");
        std::string user_input = buffer->get();

        if(!this->is_running.load(std::memory_order_relaxed)) break;
        
        logger::cout("=== THREAD №2 received user input ===");
        std::cout << user_input << std::endl;
        
        logger::cout("=== THREAD №2 send user input ===");
        this->send_to_second_app(sum_digits(user_input));
    }
    logger::cout("=== THREAD №2 exit ===");
}

void SecondThread::send_to_second_app(int sum){
    std::string data = std::to_string(sum);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in sock_in;
    sock_in.sin_addr.s_addr = INADDR_ANY;
    sock_in.sin_family = AF_INET;
    sock_in.sin_port = htons(8080);

    sendto(sockfd, data.c_str(), data.size(), 0, (struct sockaddr*)&sock_in,sizeof(sock_in));

    close(sockfd);
}

int SecondThread::sum_digits(const std::string &user_input){
    return std::accumulate(user_input.begin(), user_input.end(), 0, [](int a, char b){
            if(std::isdigit(b)){
                return a + b - '0';
            }
            return a;
        }
    );
}

void SecondThread::stop(){
    this->is_running.store(false, std::memory_order_relaxed);
}