#pragma once

#include "Consumer.h"
#include "Producer.h"

class Scheduler
{
public:

    Scheduler(Data& data, std::vector<std::unique_ptr<Consumer>>& consumers, std::vector<std::unique_ptr<Producer>>& producers, Reporter& reporter)
        : m_data(data)
        , m_consumers(consumers)
        , m_producers(producers)
        , m_reporter(reporter)
    {
        // nothing to do
    }

    void run()
    {
        while (m_running)
        {
            std::this_thread::sleep_for(c_tick);
            if (m_data.get_produced_items() > 10) {
                m_running = false;
                m_reporter.report("scheduler stopping");
                break;
            }
            m_reporter.report("scheduler continue");
        }

        for (std::size_t i = 0; i < m_consumers.size(); ++i) {
            m_consumers[i]->stop();
        }
        for (std::size_t i = 0; i < m_producers.size(); ++i) {
            m_producers[i]->stop();
        }
    }

    Data& m_data;
    std::vector<std::unique_ptr<Consumer>>& m_consumers;
    std::vector<std::unique_ptr<Producer>>& m_producers;
    Reporter m_reporter;
    bool m_running{ true };
};
