/**************************************************************
* Name     :  ex42-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月24日
**************************************************************/



/*
example 42.4: task-based concurrency
*/


// perform a task given arguments get one result
res = task(args);

// concurrent version
// perform a task given arguments
auto handle = async(tack.args);
// ... do something else ...
// get the result
res = handle.get();


// section 42.4.1: future and promise
// section 42.4.2: promise
promise<map<string, int>> pr;
map<string, int> m;
// ... fill m with a million <string, int> pairs
pr.set_value(m);


// section 42.4.3: packaged_task
try {
    // assume that the promise is called pr
    pr.set_value(f(args));
}
catch (...) {
    pr.set_exception(current_exception());
}

int ff(int i)
{
    if (i) {
        return i;
    }
    throw runtime_error("ff(0)");
}

// store ff in pt1
packaged_task<int(int)> pt1 {ff};
// store ff in pt2
packaged_task<int(int)> pt2 {ff};
// let pt1 call ff(1);
pt1(1);
// let  pt2 call ff(0);
pt2(0);

auto v1 = pt1.get_future();
auto v2 = pt2.get_future();

try {
    cout << v1.get() << '\n';
    // will throw
    cout << v2.get() << '\n';
}
catch (exception& e) {
    cout << "exception: " << e.what() << '\n';
}

try {
    cout << ff(1) << '\n';
    cout << ff(0) << '\n';
}
catch (exception& e) {
    cout << "exception: " << e.what() << '\n';
}


using Res = /* result type for server */;
using Args = /* argument types for server */;
using PTT = Res(Args);
Sync_queue<packaged_task<PTT>> server;
// function do something
Res f(Args);
// function object
struct G {
    // function object::do something
    Res operator()(Args);
    // ...
};

// lambda
auto h = [=](Args a) { /* do something */ };
packaged_task<PTT> job1(f);
packaged_task<PTT> job2(G{});
packaged_task<PTT> job3(h);

auto f1 = job1.get_future();
auto f2 = job2.get_future();
auto f3 = job3.get_future();

server.put(move(job1));
server.put(move(job2));
server.put(move(job3));

auto r1 = f1.get();
auto r2 = f2.get();
auto r3 = f3.get();


// section 42.4.4: future
template<typename T>
vector<T> wait_for_all(vector<future<T>>& vf)
{
    vector<T> res;
    for (auto& fu : vf) {
        res.push_back(fu.get());
    }
    return res;
}

future_status s = fu.wait_for(seconds{0});

// regturn index of ready future
// if no future is ready, wait for d before trying again
template<typename T>
int wait_for_any(vector<future<T>>& vf, steady_clock::duration d)
{
    while(true) {
        for (int i = 0; i != vf.size(); ++i) {
            if (!vf[i].valid()) {
                continue;
            }
            switch (vf[i].wait_for(seconds{0})) {
                case future_status::ready:
                    return i;
                case future_status::timeout:
                    break;
                case future_status::deferred:
                    throw runtime_error("wait_for_any(): defeered future");
            }
        }
        this_thread::sleep_for(d);
    }
}


// section 42.4.5: shared_future
// section 42.4.6: async()
double square(int i) { return i * i; }
future<double> fd = async(suqare, 2);
double d = fd.get();

auto fd = async(square, 2);
auto d = fd.get();

vid user()
{
    auto handle = async([](){return input_interaction_manager();});
    // ...
    auto input = handle.get();
    // ...
}


// section 42.4.7:  a parallel find() example
// data to be searched
extern vector<Record> goods;

template<typename Pred>
Record* find_rec(vector<Record>& vr, int first, int last, Pred pr)
{
    vector<Record>::iterator p = std::find_if(vr.begin() + first, vr.begin() + last, pr);
    if (p == vr.begin() + last) {
        // at end: no record found
        return nullptr;
    }
    // found return a pointer to the element
    return &*p;
}

// number of records for a linear search
const int grain = 50000;

template<typename Pred>
Record* pfind(vector<Record>& vr, Pred pr)
{
    assert(vr.size() % grain == 0);
    vector<future<Record*>> res;

    for (int i = 0; i != vr.size(); i += grain) {
        res.push_back(async(find_rec<Pred>, ref(vr), i, i + grain, pr));
    }
    // look for a result in the future
    for (int i = 0; i != res.size(); ++i) {
        if (auto p = res[i].get()) {
            // did the task find a match?
            return p;
        }
    }
    // no match found
    return nullptr;
}

void find_cheap_red()
{
    assert(goods.size() % grain == 0);
    Record* p = pfind(goods,
        [](Record& r) { return r.price < 200 && r.color == Color::red; }
    );
    if (p) {
        cout << "record " << *p << '\n';
    }
    else {
        cout << "not found\n";
    }
}

template<typename Pred>
Record* pfind_any(vector<Record>& vr, Pred pr)
{
    assert(vr.size() % grain == 0);
    vector<future<Record*>> res;

    for (int i = 0; i != vr.size(); i += grain) {
        res.push_back(async(find_rec<Pred>, ref(vr), i, i +grain, pr));
    }
    for (int count = res.size(); count; --count) {
        // find a completed task
        int i = wait_for_any(res, microseconds{10});
        if (auto p = res[i].get()) {
            return p;
        }
    }
    // no match found
    return nullptr;
}

template<typename Pred>
vector<Record*> find_all_rec(vector<Record>& vr, int first, int last , Pred pr)
{
    vector<Record*> res;
    for (int i = first; i != last; ++i) {
        if (pr(vr[i])) {
            res.push_back(&vr[i]);
        }
    }
    return res;
}

template<typename Pred>
vector<Record*> pfind_all(vector<Record>& vr, Pred pr)
{
    assert(vr.size() % grain == 0);
    vector<future<vector<Record*>>> res;

    for (int i = 0; i != vr.size(); i += grain) {
        res.push_back(async(find_all_rec<Pred>, ref(vr), i, i + grain, pr));
    }
    vector<vector<Record*>> r2 = wait_for_all(res);
    vector<Record*> r;
    for (auto& x : r2) {
        // merge results
        for (auto p : x) {
            r.push_back(p);
        }
    }
    return r;
}


void find_all_cheap_red()
{
    assert(goods.size() % grain == 0);
    auto vp = pfind_all(goods, [](Record& r){ return r.price<200 && r.color==Color::red;});
    for (auto p : vp) {
        cout << "record " << *p << '\n';
    }
}

// sequencial versions
void just_find_cheap_red()
{
    auto p = find_if(goods.begin(), goods.end(),
        [](Record& r) { return r.price < 200 && r.color == Color::red; }
    );
    if (p != goods.end()) {
        cout << "record " << *p << '\n';
    }
    else {
        cout << "not found\n";
    }
}

void just_find_all_cheap_red()
{
    auto vp = find_all_rec(goods, 0, goods.size(),
        [](Record& r) { return r.price < 200 && r.color == Color::red}
    );
    for (auto p : vp) {
        cout << "record " << *p << '\n';
    }
}

