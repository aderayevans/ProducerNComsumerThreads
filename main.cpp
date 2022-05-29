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
#include <thread>
#include <future>
#include <condition_variable>
#include <mutex>

void threadFunc(std::mutex &mtx)
{
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "I locked the mutex" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main(int argc, char* argv[])
{
    std::mutex mtx;
    std::thread th = std::thread(threadFunc, std::ref(mtx));
    std::cout << "Done spawning threads. Now waiting for them to join:\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "I am inside the main thread" << std::endl;

    std::cout << "Ending . . ." << std::endl;
    th.join();
    std::cout << "End of code." << std::endl;
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

//   return 0;
// }