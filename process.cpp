#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "process.hpp"
// #include "handlefile.hpp"

// typedef std::string LinkedList;
// const int LISTSIZE = 5;

Process::Process(std::string filename)
{
    LISTSIZE = 5;
    current_size = 0;
    // read(filename);
    // spawnThreads();
    producer = new Producer(LISTSIZE);
    consumer = new Consumer(LISTSIZE);

    start();
}

void Process::quit()
{
    producer->stop();
    consumer->stop();
}

void Process::start()
{
    std::thread producer_thread(&Producer::insert, producer, 
                                    std::ref(sharedList), std::ref(current_size),
                                    std::ref(mtx), std::ref(convar));
    std::thread consumer_thread(&Consumer::extract, consumer, 
                                    std::ref(sharedList), std::ref(current_size),
                                    std::ref(mtx), std::ref(convar));

    std::cout << "Process started" << std::endl;
    std::cout << current_size << std::endl;

    producer_thread.join();
    consumer_thread.join();
}

void Process::insert()
{
    if (current_size == LISTSIZE)
    {
        //waiting
        std::cout << "List is full" << std::endl;
        return;
    }
    std::string str;
    std::cout << "Input: ";
    std::cin >> str;

    insert(str);
}

void Process::extract()
{
    if (current_size == 0)
    {
        //waiting
        std::cout << "List is empty" << std::endl;
        return;
    }
    std::string str;
    std::cout << "Input: ";
    std::cin >> str;
    extract(str);
}

void Process::insert(std::string job)
{
    // HandleFile::write_file<LinkedList>(filename, WRITER_MODE::CLEAR);

    producer->add_queue(job);
}

void Process::extract(std::string job)
{
    // HandleFile::write_file<LinkedList>(filename, WRITER_MODE::CLEAR);

    consumer->add_queue(job);
}

void Process::print()
{
    for (auto &val:sharedList)
        std::cout << val << std::endl;
}

void Process::read()
{
    // sharedList = HandleFile::read_file<LinkedList>(filename);
}

void Process::save()
{
    // HandleFile::write_file<LinkedList>(filename, WRITER_MODE::TRUNCATE);
}