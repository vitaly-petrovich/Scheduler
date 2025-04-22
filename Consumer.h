#pragma once

#include <thread>

#include "Data.h"
#include "Reporter.h"

class Consumer
{
public:
    Consumer(Data& data, Reporter& reporter)
        : m_data(data)
        , m_reporter(reporter)
    {
        // nothing to do
    }

    void run()
    {
        while (m_running) {
            std::this_thread::sleep_for(c_tick);

            auto item = m_data.get();
            if (!item) continue;

            m_reporter.report("consumed " + std::to_string(item->m_value));
        }
        m_reporter.report("consumer stopping");
    }

    void start()
    {
        if (m_thread)
            return;

        m_thread = std::make_unique<std::thread>(&Consumer::run, this);
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
