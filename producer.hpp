#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <future>
#include <condition_variable>
#include <mutex>
#include "linkedlist.hpp"

class Producer
{
public:
    Producer(int max_size)
        : max_size(max_size)
    {
    }

    void add_queue(std::string val)
    {
        queue.push(val);
    }

    void stop()
    {
        exit_thread_flag = true;
    }
    
    void insert(LinkedList<std::string>& sharedList, 
        int& current_size,
        std::mutex& mtx,
        std::condition_variable& convar)
    {
        std::unique_lock <std::mutex> lock(mtx);
        while (!exit_thread_flag)
        {
            while (queue.empty() || current_size == max_size)
            {
                convar.wait(lock);
            }

            sharedList.push_back(queue.front());
            queue.pop();
            current_size++;

            convar.notify_all();
        }
    }


    int max_size;
    std::atomic<bool> exit_thread_flag{false};
    std::queue<std::string> queue;
};

#endif