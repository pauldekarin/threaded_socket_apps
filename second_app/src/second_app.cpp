

#include "../second_app.hpp"

SecondApp::SecondApp():
    controller(StateController()),
    listener(std::make_shared<Listener>()),
    writer(Writer()){
}

void SecondApp::init(){
    this->listener->bind_socket();  
    
    this->controller.insert_observer(shared_from_this());
    this->controller.insert_observer(listener);
}

void SecondApp::stop(){
    if(!this->is_running) return;
    this->is_running = false;
}

void SecondApp::exec(){
    logger::cout("SECOND APP","starts");
    while(true){
        logger::cout("SECOND APP","waiting message");
        std::string msg = this->listener->listen();

        if(!this->is_running) break;

        logger::cout("SECOND APP","received message");
        this->writer.write(msg);
    }
    logger::cout("SECOND APP","stop");
}



int main(){
    logger::cout("APPLICATION №2" ,"Starts");
    std::shared_ptr<SecondApp> app = std::make_shared<SecondApp>();
    app->init();
    app->exec();

    logger::cout("APPLICATION №2", "Exit");
    exit(EXIT_SUCCESS);
}