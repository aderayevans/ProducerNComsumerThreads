#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include <string>
#include <vector>
#include <queue>

struct Producer
{
public:
    Producer()
    {}

    void add_queue(std::string val)
    {
        queue.push(val);
    }
    
    void insert(std::vector<std::string>& sharedList, int LISTSIZE, int& current_size)
    {
        sharedList.push_back(queue.front());
        queue.pop();
        current_size++;
    }

    std::queue<std::string> queue;
};

#endif