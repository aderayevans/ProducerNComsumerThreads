#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <future>
#include <condition_variable>
#include <mutex>
#include "linkedlist.hpp"

class Consumer 
{
public:
    Consumer(int max_size)
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

    void extract(LinkedList<std::string>& sharedList, 
        int& current_size,
        std::mutex& mtx,
        std::condition_variable& convar)
    {
        std::unique_lock <std::mutex> lock(mtx);
        while (!exit_thread_flag)
        {
            while (queue.empty() || current_size == 0)
            {
                convar.wait(lock);
            }
            
            std::string temp = queue.front();
            // auto it = find(sharedList.begin(), sharedList.end(), temp);
            // if (it != sharedList.end())
            {
                // sharedList.erase(it);
                sharedList.erase(sharedList.begin());
                current_size--;
            }
            // else std::cout << "There is no " + temp + " in sharedList\n";
            queue.pop();

            convar.notify_all();
        }
    }

    int max_size;
    std::atomic<bool> exit_thread_flag{false};
    std::queue<std::string> queue;
};

#endif 