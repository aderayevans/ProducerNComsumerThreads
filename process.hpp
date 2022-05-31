#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <vector>
#include <string>
#include "producer.hpp"
#include "consumer.hpp"
#include "linkedlist.hpp"

class Process 
{
public:
    Process(std::string);
    void print();
    void start();
    void quit();
    void insert();
    void extract();
    void insert(std::string);
    void extract(std::string);
    void read();
    void save();

private:
    // std::vector<std::string> sharedList;
    LinkedList<std::string> sharedList;
    int current_size;
    std::string filename;
    Producer *producer;
    Consumer *consumer;
    std::mutex mtx;
    std::condition_variable convar;
    int max_size;
};

#endif