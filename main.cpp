/*
Create a Producer thread and a Consumer thread 
Using a shared LinkedList list of jobs in queue
Using Condition Variable to control the insertion 
    and extraction from this list so that 
    we do not 
        insert into list if it is full or 
        remove from it of it is empty 
*/

#include <iostream>
#include <string>

const std::string filename = "sharedList.txt";

#include "process.hpp"
#include "menuchoice.hpp"

void start();
void printMenu();

int main(int argc, char* argv[])
{
    start();

    return 0;
}

void start()
{
    std::string menuInput;

    printMenu();

    Process proc = Process(filename);


    while (true)
    {
        std::cout << "> ";
        std::cin >> menuInput;

        switch(hashTheChoice(menuInput))
        {
            case menuChoice::quit:
                proc.quit();
                exit(0);
            case menuChoice::help:
                printMenu();
                break;
            case menuChoice::print:
                proc.print();
                break;
            case menuChoice::insert:
                proc.insert();
                break;
            case menuChoice::extract:
                proc.extract();
                break;
            case menuChoice::save:
                proc.save();
                break;
            case menuChoice::wrong:
                std::cout << "Syntax Error !!!" << std::endl;
                printMenu();
                break;
        }
    }
}


// #include <iostream>       // std::cout
// #include <thread>         // std::thread, std::this_thread::sleep_for
// #include <chrono>         // std::chrono::seconds

// void pause_thread(int n) 
// {
// //   std::this_thread::sleep_for (std::chrono::seconds(n));
//   std::cout << "pause of " << n << " seconds ended\n";
// }

// int main() 
// {
//   std::cout << "Spawning 3 threads...\n";
//   std::thread t1 (pause_thread,1);
//   std::thread t2 (pause_thread,2);
//   std::thread t3 (pause_thread,3);
//   std::cout << "Done spawning threads. Now waiting for them to join:\n";
//   t1.join();
//   t2.join();
//   t3.join();
//   std::cout << "All threads joined!\n";


    // std::mutex mtx;
    // std::thread th = std::thread(threadFunc, std::ref(mtx));
    // std::cout << "Done spawning threads. Now waiting for them to join:\n";

    // std::unique_lock<std::mutex> lock(mtx);

    // std::cout << "I am inside the main thread" << std::endl;

//   return 0;
// }