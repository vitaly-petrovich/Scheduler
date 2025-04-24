#pragma once

#include <string>
#include <iostream>
#include <mutex>

class Reporter
{
public:
    void report(const std::string& data)
    {
        std::string out(data + "\n");
        std::cout << out;
    }
};
