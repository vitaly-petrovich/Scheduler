#pragma once

#include <string>
#include <iostream>

class Reporter
{
public:
    void report(const std::string& data)
    {
        std::string out(data + "\n");
        std::cout << out;
    }
};
