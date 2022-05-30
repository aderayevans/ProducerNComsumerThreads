#ifdef PRODUCER_HPP
#define PRODUCER_HPP

#include <string>
#include <vector>

struct Producer
{
public:
    Producer()
    {}

    void add_queue(std::string val)
    {
        queue.push_back(val);
    }
    
    void insert(std::vector<std::string>& sharedList, int LISTSIZE, int& current_size)
    {
        sharedList.push_back(queue.front());
        queue.pop_front();
        current_size++;
    }

    std::vector<std::string> queue;
};

#endif