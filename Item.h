#pragma once

#include <limits>

using namespace std::chrono_literals;

const auto c_tick = 2000ms;
class Item
{
public:
    static constexpr int invalid = std::numeric_limits<int>::max();

    Item() {}
    Item(int value)
        : m_value(value)
    {
        // nothing to do
    }

    int m_value{ 0 };
};