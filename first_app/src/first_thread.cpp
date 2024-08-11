#include "../first_thread.hpp"

FirstThread::FirstThread(std::shared_ptr<Buffer> buffer):
    buffer(buffer){

}
FirstThread::~FirstThread(){

}

void FirstThread::exec(){
    logger::cout("=== THREAD №1 run ===");
    while(this->is_running.load(std::memory_order_relaxed)){

        if(user_input_something()){
            logger::cout("=== THREAD №1 get user input ===");
            std::string user_input;
            std::getline(std::cin, user_input);

            logger::cout("=== THREAD №1 validate user input ===");
            if(validate_user_input(user_input)){
                logger::cout("=== THREAD №1 process user input ===");
                process_user_input(user_input);

                logger::cout("=== THREAD №1 set user input ===");
                buffer->set(user_input);
            }else{
                logger::cout("=== THREAD №1 incorrect user input ===");
            }
        }
    }
    logger::cout("=== THREAD №1 exit ===");
}

bool FirstThread::validate_user_input(const std::string &user_input){
    return std::all_of(user_input.begin(), user_input.end(), [](char chr){return std::isdigit(chr);}) && 
        user_input.size() <= MAX_SIZE;
}

void FirstThread::sort_user_input(std::string &user_input){
    std::sort(user_input.rbegin(), user_input.rend());
}
void FirstThread::replace_even_elements_user_input(std::string &user_input){
    user_input = std::regex_replace(user_input, std::regex("[02468]"), "KB");
}

void FirstThread::process_user_input(std::string &user_input){
    sort_user_input(user_input);
    replace_even_elements_user_input(user_input);
}

bool FirstThread::user_input_something(){
    fd_set fds;
    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    FD_ZERO(&fds);
    FD_SET(fileno(stdin), &fds);

    return select(fileno(stdin) + 1, &fds, nullptr, nullptr, &timeout) > 0;
}   

void FirstThread::stop(){
    this->is_running.store(false, std::memory_order_relaxed);
}