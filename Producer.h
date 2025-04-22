#pragma once

#include <chrono>
#include <random>
#include <thread>

#include "Reporter.h"
#include "Data.h"

class Producer
{
public:
    Producer(Data& data, Reporter& reporter)
        : m_data(data)
        , m_reporter(reporter)
    {
        // nothing to do
    }

    void run()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(1, 10);

        while (m_running) {
            std::this_thread::sleep_for(c_tick);
            Item item(dist(rd));
            m_reporter.report("produced " + std::to_string(item.m_value));
            m_data.add(item);
        }
        m_reporter.report("producer stopping");
    }

    void start()
    {
        if (m_thread)
            return;

        m_thread = std::make_unique<std::thread>(&Producer::run, this);
    }

    void stop()
    {
        m_running = false;

        if (!m_thread || !m_thread->joinable())
            return;

        m_thread->join();
    }

    Data& m_data;
    Reporter m_reporter;
    std::atomic<bool> m_running{ true };
    std::unique_ptr<std::thread> m_thread;
};
