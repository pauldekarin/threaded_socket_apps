#ifndef WRITER_HPP
#define WRITER_HPP

#include <string>
#include <iostream>

class Writer{

public:
    Writer() = default;
    ~Writer() = default;

    void write(const std::string &msg);
};

#endif