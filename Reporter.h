#pragma once

#include <string>
#include <iostream>
#include <syncstream>

class Reporter
{
public:
    void report(const std::string& data)
    {
        std::osyncstream(std::cout) << data << std::endl;
    }
};
