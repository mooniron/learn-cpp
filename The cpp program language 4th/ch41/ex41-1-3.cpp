/**************************************************************
* Name     :  ex41-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月23日
**************************************************************/



/*
example 41.3: atomics
*/


enum memory_order {
    memory_order_relaxed,
    memory_order_consume ,
    memory_order_acquire ,
    memory_order_release ,
    memory_order_acq_rel,
    memory_order_seq_cst
};

//thread 1:
r1 = y.load(memor y_order_relaxed);
x.store(r1,memory_order_relaxed);

//thread 2:
r2 = x.load(memory_order_relaxed);
y.store(42,memory_order_relaxed);


[[carries_dependency]] struct foo* f(int i)
{
    // let the caller use memory_order_consume for the result:
    return foo_head[i].load(memory_order_consume);
}


// section 41.3.1: atomic types
atomic<int> val = 0;
// ...
// read current value
int expected = val.load();
do {
    // calculate new value
    int next = fct(expected);
} while (!val.compare_exchange_weak(expected, next));   // write next to val or to expected


//the shared head of a linked list
extern atomic<Link∗>head;
//make a link ready for insertion
Link∗ nh = newLink(data,nullptr);
//read the shared head of the list
Link∗ h=head.load();
do {
    //if so, inser t elsewhere
    if (h−>data<data) break;
    //next element is the previous head
    nh−>next = h;

} while (!head.compare_exchang e_weak(h,nh)); //write nh to head or to h


// we need a lock to initialize an X
X x;
// the mutex to be used to lock x during initialization
mutex lx;
// an atomic used to minimize locking
atomic<bool> x_init {false};

void some_code()
{
    if (!x_init) {
        // proceed if x is uninitialized
        lx.lock();
        if (!x_init) {
            // proceed if x is still uninitialized
            // ... initialize x ...
            x_init = true;
        }
        lx.unlock();
    }
    // ... use x ...
}


// section 41.3.2: flags and fences
// section 41.3.2.1: atomic flags
class spin_mutex {
    atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    void lock() {while(flag.test_and_set());}
    void unlock() { flag.clear(); }
};


// section 41.3.2.2: fences
