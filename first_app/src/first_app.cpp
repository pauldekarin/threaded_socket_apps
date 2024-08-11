#include "../first_app.hpp"

FirstApp::FirstApp(){
    this->controller = std::make_shared<StateController>();
    this->buffer = std::make_shared<Buffer>();

    this->controller->insert_observer(this->buffer);
}
FirstApp::~FirstApp(){
    this->stop();
}

void FirstApp::stop(){
    if(!this->is_running) return;
    this->is_running = false;
}

void FirstApp::exec(){
    std::shared_ptr<FirstThread> f_th = std::make_shared<FirstThread>(this->buffer);
    std::shared_ptr<SecondThread> s_th = std::make_shared<SecondThread>(this->buffer);

    this->first_thread = std::thread{&FirstThread::exec, f_th};
    this->second_thread = std::thread{&SecondThread::exec, s_th};

    this->controller->insert_observer(f_th);
    this->controller->insert_observer(s_th);

    this->first_thread.join();
    this->second_thread.join();
}


int main(){
    logger::cout("Application №1", "Starting");

    FirstApp app = FirstApp();
    app.exec();

    logger::cout("Application №1", "Closing");
}