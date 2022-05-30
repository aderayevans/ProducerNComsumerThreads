#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <future>
#include <condition_variable>
#include <mutex>

class Producer
{
public:


    Producer(int LISTSIZE)
        : LISTSIZE(LISTSIZE)
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
    
    void insert(std::vector<std::string>& sharedList, 
        int& current_size,
        std::mutex& mtx,
        std::condition_variable& convar)
    {
        while (!exit_thread_flag)
        {
            std::unique_lock<std::mutex> lock(mtx);
            while (queue.size() == 0 || sharedList.size() == LISTSIZE)
            {
                std::cout << "Waiting .. \n";
                convar.wait(lock);
            }
            sharedList.push_back(queue.front());
            queue.pop();
            current_size++;
            convar.notify_all();
        }
    }


    int LISTSIZE;
    std::atomic<bool> exit_thread_flag{false};
    std::queue<std::string> queue;
};

#endif