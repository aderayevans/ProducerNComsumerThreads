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

class Consumer 
{
public:
    Consumer()
    {   
    }

    Consumer(int LISTSIZE)
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

    void extract(std::vector<std::string>& sharedList, 
        int& current_size,
        std::mutex& mtx,
        std::condition_variable& convar)
    {
        while (!exit_thread_flag)
        {
            std::unique_lock<std::mutex> lock(mtx);
            while (queue.size() == 0 || LISTSIZE == 0)
            {
                std::cout << "Waiting .. \n";
                convar.wait(lock);
            }
            std::string temp = queue.front();
            auto it = find(sharedList.begin(), sharedList.end(), temp);
            if (it != sharedList.end())
            {
                sharedList.erase(it);
                current_size--;
                queue.pop();
            }
            else std::cout << "There is no " + temp + " in sharedList\n";
            convar.notify_all();
        }
    }

    int LISTSIZE;
    std::atomic<bool> exit_thread_flag{false};
    std::queue<std::string> queue;
};

#endif 