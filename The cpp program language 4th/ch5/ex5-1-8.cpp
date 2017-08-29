/**************************************************************
* Name     :  ex5-1-8.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.3 :concurrency
    5.3.4 : sharing data
    5.3.4.1 : waiting for events
*/



#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono; using namespace std;


// object to be communicated
class Message {
    // ...
};

// the queue of messages
queue<Message> mqueue;
// the variable communicating events
condition_variable mcond;
// the locking mechanism
mutex mmutex;


// the comsumer reads and processes messages
void consumer()
{
    while (true) {
        // acquire mmutex
        unique_lock<mutex> lck{mmutex};
        // release lck and wait
        while (mcond.wait(lck))
        {
            ;   // do nothing
        }

        // re-acquire lck upon wakeup
        // get the message
        auto m = mqueue.front();
        mqueue.pop();
        // release lck
        lck.unlock();
        // process m
    }   // end while
}


void producer()
{
    while (true) {
        Message m;
        // ... fill the message ...
        // protect operations
        unique_lock<mutex> lck {mmutex};
        mqueue.push(m);
        // notify
        mcond.notify_one();
    }   // release lock (at end of scope)
}




int main() {
    auto t0 = high_resolution_clock::now();
    this_thread::sleep_for(milliseconds{20});
    auto t1 = high_resolution_clock::now();
    cout << duration_cast<nanoseconds>(t1 - t0).count() << "nanoseconds passed\n";

    return 0;
}
