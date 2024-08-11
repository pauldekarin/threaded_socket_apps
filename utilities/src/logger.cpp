#include "../logger.hpp"

namespace logger{
    #ifdef LOG
    void cout(std::string msg){
        std::cout << msg << std::endl;
    }
    #else
    void cout(std::string msg){}
    #endif
}