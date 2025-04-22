#pragma once

#include <mutex>
#include <queue>
#include <optional>
#include <atomic>

#include "Item.h"

class Data
{
public:

    void add(const Item& item) {
        std::lock_guard<std::mutex> lock(m_mutex);

        m_items.push(item);
        ++m_items_produced;
    }

    std::optional<Item> get() {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (!m_items.size())
            return std::nullopt;

        Item item = m_items.front();
        m_items.pop();
        return { item };
    }

    std::size_t get_produced_items() const
    {
        return m_items_produced;
    }

    std::atomic<std::size_t> m_items_produced{ 0 };
    std::queue<Item> m_items;
    std::mutex m_mutex;
};