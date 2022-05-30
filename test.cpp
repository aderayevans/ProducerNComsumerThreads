#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

std::vector<int> globalVector;
std::condition_variable convar;
std::mutex mtx;
// Flag telling the thread to continue or exit
std::atomic<bool> exit_thread_flag{false};

void threadFunc1()
{
    // std::cout << "Thread " << std::this_thread::get_id() << std::endl;
    while (!exit_thread_flag)
    {
        std::unique_lock<std::mutex> lock(mtx);
        while (globalVector.size() % 2 != 0)
        {
            // std::cout << "Size: " << globalVector.size() << " >> waiting(1) . . .\n";
            convar.wait(lock);
        }
        // std::cout << "Size: " << globalVector.size() << " >> push(1) . . .\n";
        globalVector.push_back(1);
        convar.notify_all();
    }
}

void threadFunc2()
{
    // std::cout << "Thread " << std::this_thread::get_id() << std::endl;
    while (!exit_thread_flag)
    {
        std::unique_lock<std::mutex> lock(mtx);
        while (globalVector.size() % 2 == 0)
        {
            // std::cout << "Size: " << globalVector.size() << " >> waiting(2) . . .\n";
            convar.wait(lock);
        }
        // std::cout << "Size: " << globalVector.size() << " >> push(2) . . .\n";
        globalVector.push_back(2);
        convar.notify_all();
    }
}

int main()
{
    std::thread t1(threadFunc1);
    std::thread t2(threadFunc2);
    std::cout << "Done spawning threads. Now waiting for them to join:\n";

    std::string str;
    while (!exit_thread_flag)
    {
        std::cout << "Input: "; std::cin >> str;
        if (str == "-q")
            exit_thread_flag = true;
        else
            std::cout << str << std::endl;
    }
    // std::this_thread::sleep_for(std::chrono::seconds(1));  // Sleep for five seconds
    // exit_thread_flag = true;  // Tell thread to exit

    t1.join();
    t2.join();
    for (auto val:globalVector)
        std::cout << val << std::endl;
}