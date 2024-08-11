#include "../logger.hpp"

namespace logger{
    #ifdef LOG
    void cout(const std::string &sender, const std::string &msg){
        std::cout << "[" << "\033[1;34m" << sender << "\033[0;0m" << "] " 
                  << msg << std::endl;
    }
    #else
    void cout(std::string msg){}
    #endif
}