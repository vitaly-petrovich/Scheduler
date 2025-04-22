#include "pch.h"
#include "Scheduler.h"

int main() {
    const std::size_t n_consumers(100);
    const std::size_t n_producers(77);

    Data data;
    Reporter reporter;
    std::vector<std::unique_ptr<Producer>> producers;
    std::vector<std::unique_ptr<Consumer>> consumers;

    producers.reserve(n_producers);
    consumers.reserve(n_consumers);

    Scheduler scheduler(data, consumers, producers, reporter);

    for (std::size_t i = 0; i < n_consumers; ++i) {
        consumers.push_back(std::make_unique<Consumer>(data, reporter));
        consumers[i]->start();
    }
    for (std::size_t i = 0; i < n_producers; ++i) {
        producers.push_back(std::make_unique<Producer>(data, reporter));
        producers[i]->start();
    }

    std::thread t2(&Scheduler::run, &scheduler);
    consumers.insert(consumers.begin(), std::make_unique<Consumer>(data, reporter));
    t2.join();

    return 0;
}