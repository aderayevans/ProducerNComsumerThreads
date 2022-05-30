#ifndef CONSUMER_HPP
#define CONSUMER_HPP
#include <algorithm>
#include <string>
#include <vector>

class Consumer 
{
public:
    Consumer()
    {}

    void add_queue(std::string val)
    {
        queue.push_back(val);
    }

    void extract(std::vector<std::string>& sharedList, int LISTSIZE, int& current_size)
    {
        std::string temp = queue.front();
        auto it = find(sharedList.begin(), sharedList.end(), temp);
        if (it != sharedList.end())
        {
            sharedList.erase(it);
            current_size--;
        }
        else std::cout << "There is no " + temp + " in sharedList\n";
    }

    std::vector<std::string> queue;
};

#endif 