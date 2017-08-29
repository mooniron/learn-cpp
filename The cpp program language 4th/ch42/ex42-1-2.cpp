/**************************************************************
* Name     :  ex42-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月24日
**************************************************************/



/*
example 42.1: introduction
example 42.2: threads
*/


// section 42.2.1: identity
void print_id(thread& t)
{
    if (t.get_id == id{}) {
        cout << "t not joinable\n";
    }
    else {
        cout << "t's id is " << t.get_id() << '\n';
    }
}


// section 42.2.2: construction
// no arguments
void f0();
// one int argument
void f1(int);

thread t1 {f0};
// error: too many arguments
thread t2 {f0, 1};
// error: too few arguments
thread t3 {f1};
thread t4 {f1, 1};
// error: too many arguments
thread t5 {f1, 1, 2};
// error: wrong type of argument
thread t6 {f1, "I'm being silly"};

template<typename T>
class Sync_queue<T> {
    // a queue proulding put() and get() without data races
    // ...
};

struct Consumer {
    Sync_queue<Message>& head;
    Consumer(Sync_queue<Message>& q) : head(q) { }
    // get messages from head
    void operator()();
};

struct Producer {
    Sync_queue<Message>& tail;
    Producer(Sync_queue<Message>& q) : tail(q) { }
    // put messages on tail
    void operator()();
};

Sync_queue<Message> mq;
// make tasks and "wire them together"
Consumer c {mq};
Producer p {mq};
// finally start threads
thread pro {p};
thread con {c};
/// ...

void my_task(vector<double>& arg);
void test(vector<double>& v)
{
    // oops: pass a copy of v
    thread my_thread1 {my_task, v};
    // ok: pass v by reference
    thread my_thread2 {my_task, ref(v)};
    // ok: dodge the ref() problem
    thread my_thread3 {[&v]{my_task(v);}};
    // ...
}

// 1000 default threads
vector<thread> worker(1000);
for (int i = 0; i != worker.size(); ++i) {
    // ... compute argument for worker[i] and create worker thread tmp ...
    worker[i] = move(tmp);
}


// section 42.2.3: destruction
void heartbeat()
{
    while(true) {
        output(steady_clock::now());
        this_thread::sleep_for(second{1});
    }
}

void run()
{
    thread t {heartbeat};
}   // terminate because heartbeat() is still running at the end of t's scope


// section 42.2.4: join()
void tick(int n)
{
    for (int i = 0; i != n; ++i) {
        this_thread::sleep_for(second{1});
        output("Alive!");
    }
}

int main()
{
    thread timer {tick, 10};
    timer.join();
}

// warning: really poor code
void  run(inti, int n)
{
    thread t1 {f};
    thread t2;
    vector<Foo> v;
    // ...
    if (i < n) {
        thread t3 {g};
        // ...
        // move t3 to outer scope
        t2 = move(t3);
    }
    // might throw
    v[i]  = Foo{};
    // ...
    t1.join();
    t2.join();
}

struct guarded_thread : thread {
    using thread::thread;
    ~guarded_thread()
    {
        if (t.joinable()) {
            t.join();
        }
    }
};

// simple use of a guard
void run2(int i, int n)
{
    guarded_thread t1 {f};
    guarded_thread t2;
    vector<Foo> v;
    // ...
    if (i < n) {
        thread t3 {g};
        // ...
        t2 = move(t3);
    }
    v[i] = Foo{};
    // ...
}


// section 42.3.5: detach()
void run2()
{
    thread t {heartbeat};
    // let heartbeat run independently
    t.detach();
}

// keep otherwise detached threads here
vector<thread> my_threads;

void run()
{
    thread t {heartbeat};
    my_threads.push_back(move(t));
    // ...
    my_threads.emplace_back(tick, 1000);
}

void monitor()
{
    for (thread& t : mythreads) {
        cout << "thread " << t.get_id() << '\n';
    }
}

// don't do this
void home()
{
    int var;
    thread disaster {[&]{ this_thread::sleep_for(second{7.3}); ++var; }};
    disaster.detach();
}


// section 42.2.6: namespace this_thread
void helper(thread& t)
{
    thread::idme {this_thread::get_id()};
    // if (t.get_id() != me) {
        t.join();
    }
    // ...
}


// section 42.2.7: killing a thread
// section 42.2.8: thread_local data
template<typename K, typenane V>
class Map {
public:
    Map();
    // ...
    // set default for all Maps of type  Map<K, V>
    static void set_default(const K&, V&);
private:
    static pair<const K, V> default_value;
};

// somewhere inthread 1:
Map<string, int>::set_default("Heraclides", 1);
// somewhere in thread2
Map<string, int>::set_default("Zeno", 1);

template<typename K, typename V>
class Map {
    // ...
private:
    static thread_local pair<const K, V> default_value;
};

