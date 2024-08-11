#include "../controller.hpp"

StateController::StateController(){
    if(this->instance == nullptr){
        this->instance = this;
    }   
    std::signal(SIGINT, StateController::catch_sigint);
}

StateController::~StateController(){
    if(this->is_running.load(std::memory_order_relaxed)){
        this->stop_all_observers();
    }
}

void StateController::stop_all_observers(){
    logger::cout("STATE CONTROLLER","notify observers to stop working ");
    for(std::shared_ptr<Observer> observer : this->observers){
        observer->stop();
    }
    this->is_running.store(false, std::memory_order_relaxed);
}

void StateController::insert_observer(std::shared_ptr<Observer> observer){
    this->observers.push_back(observer);
}

void StateController::catch_sigint(int signum){
    logger::cout("STATE CONTROLLER","catch Ctrl + C");
    instance->stop_all_observers();
}