/**************************************************************
* Name     :  ex31-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月30日
**************************************************************/



/*
example 31.5: container adaptors
*/



// section 31.5.1: stack
template<typename T, typename C = deque<T>>
class stack {
public:
    using value_type = typename C::value_type;
    using reference = typename C::reference;
    using const_reference = typename C::const_reference;
    using size_type  typename C::size_type;
    using container_type = C;
public:
    // copy from container
    explicit stack(const C&);
    // move from container
    explicit stack(C&& = c{});
    // default copy, move, assignment, destructor
    // default container, allocator a
    template<typename A>
    explicit stack(const A& a);
    // elements from c, allocator a
    template<typename A>
    stack(const C& c, const A& a);
    template<typename A>
    stack(C&&, const A&);
    template<typename A>
    stack(const stack&, const A&);
    template<typename A>
    stack(stack&&, const A&);

    bool empty() const { return c.empty(); }
    size_type size() cnst { return c.size(); }
    reference top() { return c.back(); }
    const_reference top() const { return c.back(); }
    void push(const value_type& x) { c.push_back(x); }
    void push(value_type&& x) { c.push_back(std::move(x)); }
    // pop the last element
    void pop() { c.pop_back(); }

    template<typename... Args>
    void emplace(Args&&... args)
    {
        c.emplace_back(std::forward<Args>(args)...);
    }

    void swap(stack& s) noexcept(noexcept(swap(c, s.c)))
    {
        // be sure to use the standard swap()
        using std::swap;
        swap(c.s, c);
    }

protected:
    C c;
};


// uses a deque<char> to store elements
stack<char> s1;
// uses a vector,int> to store elements
stack<int, vector<int>> s2;

void f()
{
    stack<int> s;
    s.push(2);
    if (s.empty()) {
        // underflow is preventable
        // don't pop
    }
    else {
        // but not impossible
        // fine; s.size() becomes 0
        s.pop();
        // undefined effect, probably bad
        s.pop();
    }
}

void f2(stack<char>& s)
{
    if (s.top() == 'c') {
        // optionally remove optional initial 'c'
        s.pop();
    }
    // ...
}


// section 31.5.2: queque
template<typename T, typename C = deque<T>>
class queue {
public:
    // ... like stack ...
    // pop the first element
    void pop() { c.pop_front(); }
};


void server(queue<Message>& q, mutex& m)
{
    while (!q.empty()) {
        Message mess;
        {
            // lock while extracting message
            lock_guard<mutex> lck(m);
            // somebody else got the message
            if (q.empty()) {
                return;
            }
            mess = q.front();
            q.pop();
        }
        // serve request
    }
}


// section 31.5.3: priority_queue
template<typename T, typename C = vector<T>, typename Cmp = less<typename C::value_type>>
class priority_queue {
protected:
    C c;
    Cmp comp;
public:
    priority_queue(const Cmp& x, const C&);
    explicit priority_queue(const Cmp& x = Cmp{}, C&& = C{});
    template<typename In>
    // insert [b:e) into c
    priority_queue(In b, In e, const Cmp& x, const C& c);
    // ...
};

struct Message {
    int priority;
    bool operator<(const Message& x) const { return priority < x.priority; }
    // ...
};

void server(priority_queue<Message>& q, mutex& m)
{
    while (!q.empty()) {
        Message mess;
        {
            // hold lock while extracting message
            lock_guard<mutex> lck(m);
        }
        // somebody else got the message
        if (q.empty()) {
            return;
        }
        mess = q.top();
        q.pop();
    }
    // serve highest priority request
}

