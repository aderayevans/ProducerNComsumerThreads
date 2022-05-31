#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "process.hpp"
#include "menuchoice.hpp"

const int LISTSIZE = 5;

Process::Process(std::string filename)
    : filename(filename)
{
    current_size = 0;
    max_size = LISTSIZE;
    // read(filename);
    // spawnThreads();
    producer = new Producer(max_size);
    consumer = new Consumer(max_size);

    start();
}

void Process::start()
{
    std::string menuInput;

    printMenu();


    std::thread producer_thread(&Producer::insert, producer, 
                                    std::ref(sharedList), std::ref(current_size),
                                    std::ref(mtx), std::ref(convar));
    std::thread consumer_thread(&Consumer::extract, consumer, 
                                    std::ref(sharedList), std::ref(current_size),
                                    std::ref(mtx), std::ref(convar));

    while (true)
    {
        std::cout << "> ";
        std::cin >> menuInput;

        switch(hashTheChoice(menuInput))
        {
            case menuChoice::quit:
                quit();
                exit(0);
            case menuChoice::help:
                printMenu();
                break;
            case menuChoice::print:
                print();
                break;
            case menuChoice::insert:
                insert();
                break;
            case menuChoice::extract:
                extract();
                break;
            case menuChoice::save:
                save();
                break;
            case menuChoice::wrong:
                std::cout << "Syntax Error !!!" << std::endl;
                printMenu();
                break;
        }
    }

    producer_thread.join();
    consumer_thread.join();
}

void Process::insert()
{
    // if (current_size == max_size)
    // {
    //     //waiting
    //     std::cout << "List is full" << std::endl;
    //     return;
    // }
    std::string str;
    std::cout << "Input: ";
    std::cin >> str;

    insert(str);
    {
        std::lock_guard<std::mutex> lock(mtx);
        convar.notify_all();
    }
}

void Process::extract()
{
    // if (current_size == 0)
    // {
    //     //waiting
    //     std::cout << "List is empty" << std::endl;
    //     return;
    // }
    std::string str;
    std::cout << "Input: ";
    std::cin >> str;

    extract(str);
    {
        std::lock_guard<std::mutex> lock(mtx);
        convar.notify_all();
    }
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
    std::cout << "List size: " << sharedList.size() << std::endl;
    // for (auto &val:sharedList)
    //     std::cout << val << std::endl;

    for (auto iterator = sharedList.begin();
            iterator != sharedList.end(); iterator++)
    {
        std::cout << *iterator << " ";
    }
}

void Process::read()
{
    // sharedList = HandleFile::read_file<LinkedList>(filename);
}

void Process::save()
{
    // HandleFile::write_file<LinkedList>(filename, WRITER_MODE::TRUNCATE);
}

void Process::quit()
{
    producer->stop();
    consumer->stop();
}