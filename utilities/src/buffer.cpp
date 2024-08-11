#include "../buffer.hpp"

Buffer::Buffer():
    is_empty(true), is_running(true){

}
Buffer::~Buffer(){
    this->stop();
}

void Buffer::stop(){
    if(!this->is_running) return;
    std::lock_guard<std::mutex> locker(this->mtx);
    logger::cout("BUFFER","stop");
    this->is_running.store(false, std::memory_order_relaxed);
    cv.notify_all();
}
void Buffer::set(const std::string &user_input){
    std::unique_lock<std::mutex> locker(mtx);
    buffer.assign(user_input);
    is_empty.store(false,std::memory_order_relaxed);
    cv.notify_all();
}

std::string Buffer::get(){
    logger::cout("BUFFER","waiting data");
    std::unique_lock<std::mutex> locker(mtx);
    cv.wait(locker);
    if(!this->is_running.load(std::memory_order_relaxed)) return std::string();
    
    std::string buffer_copy{buffer.begin(), buffer.end()};
    buffer.clear();
    is_empty.store(true, std::memory_order_relaxed);
    logger::cout("BUFFER","received data");
    return buffer_copy;
}