/**************************************************************
* Name     :  ex42-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月24日
**************************************************************/



/*
example 42.3: avoiding data races
*/


// section 42.3.1: mutexes
// represent the right to se cout
mutex cout_mutex;

template<typename Arg1, typename Arg2, typename Arg3>
void write(Arg1 a1, Arg2 a2 = {}, Arg3 a3 = {})
{
    thread::id name = this_thread::get_id();
    cout_mutex.lock();
    cout << "From thread " << name << " : " << a1 << a2 << a3;
    cout_mutex.unlock();
}


// section 52.3.3.1: mutex and recursive_mutex
// initialized to "not owned by any thread"
mutex cout_mutex;

void hello()
{
    cout_mutex.lock();
    cout << "Hello, ";
    cout_mutex.unlock();
}

void world()
{
    cout_mutex.lock();
    cout << "World!";
    cout_mutex.unlock();
}

int main()
{
    thread t1 {hello};
    thread t2 {world};
    t1.join();
    t2.join();
}


extern mutex wqm;
extern list<Work> wq;

void composer()
{
    list<Work> requests;

    while (true) {
        for (int i = 0; i != 10; ++i) {
            Work w;
            // ... compose work request ...
            requests.push_back(w);
        }
        if (wqm.try_lock()) {
            // splice() requests into the list
            wq.splice(requests);
            wqm.unlock();
        }
    }
}

template<typename Arg, typename... Args>
void write(Arg a, Args tail...)
{
    cout_mutex.lock();
    cout << a;
    write(tail...);
    cout_mutex.unlock();
}

// changed to recursive_mutex to avoid deadlock
recursive_mutex cout_mutex;

template<typename Arg, typename... Args>
void write(Arg a, Args tail...)
{
    cout_mutex.lock();
    cout << a;
    write(tail...);
    cout_mutex.unlock();
}


// section 42.3.1.2: mutex errors
mutex mtx;
try {
    mtx.lock();
    // try to lock a cecond time
    mtx.lock();
}
catch (system_error& e) {
    mtx.unlock();
    cout << e.what() << '\n';
    cout << e.code() << '\n';
}


// section 42.3.1.3: timed_mutex and recursive_timed_mutex
extern timed_mutex imtx;
extern Image buf;

void next()
{
    while (true) {
        Image next_image;
        // ... compute ...
        if (imtx.try_lock(milliseconds{10})) {
            buf = next_image;
            imtx.unlock();
        }
    }
}


// section 42.3.1.4: lock_guard and unique_lock
void use(mutex& mtx, Vector<string>& vs, int i)
{
    mtx.lock();
    if (i < 0) {
        return;
    }
    string s = vs[i];
    // ...
    mtx.unlock();
}

void use(mutex& mtx, vector<string>& vs, int i)
{
    lock_guard<mutex> g {mtx};
    if (i < 0) {
        return;
    }
    string s = vs[i];
    // ...
}

vid use(mutex& mtx, vector<string>& vs, int i)
{
    if (i < 0) {
        return;
    }
    lock_guard<mutex> g {mtx};
    string s = vs[i];
    // ...
}

vid use(mutex& mtx, vector<string>& vs, int i)
{
    if (i < 0) {
        return;
    }

    string s;
    {
        lock_guard<mutex> g {mtx};
        s = vs[i];
    }
    // ...
}

mutex mts;
timed_mutes mtx2;

void use()
{
    unique_lock<defer_lock_t, mutex> lck {mtx};
    unique_lock<defer_lock_t, timed_mutex> lck2 {mtx2};
    // error: mutex does not have member try_lock_for()
    lck.try_lock_for(seconds{2});
    // ok
    lck2.try_lock_for(milliseconds{2});
    lck2.try_lock_until(steady_clock::now() + milliseconds{2});
    // ...
}

timed_mutex mtx2;
void use2()
{
    unique_lock<timed_mutex> lck2 {mtx2, milliseconds{2}};
    if (lck2.owns_lock()) {
        // acquisition succeeded:
        // ... do something ...
    }
    else {
        // timeout:
        // ... do something else ...
    }
}


// section 42.3.2: multiple locks
// protects one resource
mutex mtx1;
// protects another resource
mutex mtx2;

void task(mutex& m1, mutex& m2)
{
    unique_lock<mutex> lck1 {m1};
    unique_lock<mutex> lck2 {m2};
    // ... use resources ...
}
thread t1 {task, ref(mtx1), ref(mtx2)};
thread t2 {task, ref(mtx2), ref(mtx1)};


template<typename M1, typename... Mx>
int try_lock(M1& mtx, Mx& tail...)
{
    if (mtx.try_lock()) {
        int n = try_lock(tail...);
        if (n == -1) {
            // all locks acquired
            return -1;
        }
        // lock out
        mtx.unlock();
        return n+1;
    }
    // couldn't acquire mtx
    return 1;
}

template<typename M1>
int try_lock(M1& mtx)
{
    return (mtx.try_lock()) ? -1 : 0;
}

void task(mutex& m1, mutex& m2)
{
    unique_lock lck1 {m1, defer_lock_t};
    unique_lock lck2 {m2, defer_lock_t};
    lock(lck1, lck2);
    // ... use resources ...
}


// section 42.3.3: call_once()
class X {
public:
    X();
    // ...
private:
    // ...
    static once_flag static_flag;
    static Y static_data_for_class_X;
    static void init();
};

X::X()
{
    call_once(static_flag, init());
}

// user code
Color& default_color()
{
    static Color def {read_from_environment("background color")};
    return def;
}

// generated code
Color& default_color()
{
    static Color def;
    static_flag __def;
    call_once(__def, read_from_environment, "background color");
    return def;
}


// section 42.3.4: condition variables
enum class cv_status { no_timeout, timeout };

while (queue.empty()) {
    wait(queue_lck);
}

void simple_timer(int delay)
{
    condition_variable timer;
    // mutex protecting timer
    mutex mtx;
    auto t0 = steady_clock::now();
    // acquire mtx
    unique_lock<mutex> lck(mtx);
    // release and reacquire mtx
    timer.wait_for(lck, milliseconds{delay});
    auto t1 = steady_clock::now();
    cout << duration_cast<milliseconds>(t1 - t0).count() << "milliseconds passed\n";
}   // implicitly release mtx

template<typename T>
class Sync_queue {
public:
    void put(const T& val);
    void put(T&& val);
    void get(T& val);
private:
    mutex mtx;
    condition_variable cond;
    list<T> q;
};

template<typename T>
void Sync_queue::put(const T& val)
{
    lock_guard<mutex> lck(mtx);
    q.push_back(val);
    cond.notify_one();
}

template<typename T>
void Sync_queue::get(T& val)
{
    unique_lock<mutex> lck(mtx);
    cond.wait(lck, [this]{ return !q.empty(); });
    val = q.front();
    q.pop_front();
}

Sync_queue<Message> mq;

void producer()
{
    while (true) {
        Message m;
        // ... fill m ...
        mq.put(m);
    }
}

void consumer()
{
    while (true) {
        Message m;
        mq.get(m);
        // ... use m ...
    }
}

thread t1 {producer};
thread t2 {consumer};

void consumer()
{
    while (true) {
        Message m;
        mq.get(m, milliseconds{200});
        // ... use m ...
    }
}

template<typename T>
void Sync_queue::get(T& val, steady_clock::duration d)
{
    unique_lock<mutex> lck(mtx);
    bool not_empty = cond.wait_for(lck, d, [this]{ return !q.empty(); });
    if (not_empty) {
        val = q.front();
        q.pop_front();
    }
    else {
        throw system_error{"Sync_queue: get() timeout"};
    }
}

template<typename T>
void Sync_queue::put(T val, steady_clock::duration d, int n)
{
    unique_lock<mutex> lck(mtx);
    bool not_full = cond.wait_for(lck, d, [this]{ return q.size() < n; });
    if (not_full) {
        q.push_back(val);
        cond.notify_one();
    }
    else {
        cond.notify_all();
        throw system_error{"Sync_queue: put() timeout"};
    }
}


// section 42.3.4.1: condition_variable_any
