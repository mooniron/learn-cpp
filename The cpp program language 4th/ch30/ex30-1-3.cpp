/**************************************************************
* Name     :  ex30-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月27日
**************************************************************/



/*
example 30.4 : error handling
*/



// section 30.4.1 : exceptions
// section 30.4.1.1 : the standard exception hierarchy
class exception {
public:
    exception();
    exception(const exception&);
    exception& operator=(const exception&);
    virtual ~exception();
    virtual const char* what() const;
};

struct My_error : runtime_error {
    My_error(int x) : runtime_error{"My_error"}, interesting_value{x} { }
    int interesting_value;
};


int main()
try {
    // ...
}
catch (My_error& me) {
    // a My_error happened
    // we can use me.interesting_value and me.what()
}
catch (runtime_error& re) {
    // runtime_error happened
    // we can use re.what()
}
catch(exception& e) {
    // some standard library exception happeded
    // we can use e.what()
}
catch (...) {
    // some unmentioned exception happened
    // we can do local cleanup
}


// section 30.4.1.2 : exception propagation
template<typename E>
exception_ptr make_exception_ptr(E e) noexcept
try {
    throw e;
}
catch (...) {
    return current_exception();
}


struct My_error() : runtime_error {
    My_error(const string&);
    // ...
};

void  my_code()
{
    try {
        // ...
    }
    catch (...) {
        My_error err {"something went wrong in my_code()"};
        // ...
        throw_with_nested(err);
    }
}

void user()
{
    try {
        my_code();
    }
    catch (My_error& err) {
        // ... clear up My_error problems ...
        try {
            // re-throw the nested exception, if any
            rethrow_if_nested(err);
        }
        catch (Some_error& err2) {
            // ... clear up Some_error problems ...
        }
    }
}


// section 30.4.1.3: terminate()


// section 30.4.2: assertions
template<typename T>
void draw_all(vector<T*>& v)
{
    static_assert(Is_base_of<Shape, T>(), "non-Shape type for draw_all()");

    for (auto p : v) {
        assert(p != nullptr);
        p->draw();
        // ...
    }
}


// section 30.4.3 : system_error
oftream& open_file(const string& path)
{
    // split into {path, name}
    auto dn = split_into_directory_and_name(path);
    // ask "the system" about the path
    error_code err {does_directory_exist(dn.first)};
    if (err) {
        // err != 0 means error
        // see if anything can be done
        if (cannot_handle_err) {
            throw system_error(err);
        }
    }

    return ofstream{path};
}


// section 30.4.3.1 : error codes
class error_code {
public:
    // representation: {value, category} of type {int, const error_category*}
};


// section 30.4.3 : system_error
oftream& open_file(const string& path)
{
    // split into {path, name}
    auto dn = split_into_directory_and_name(path);
    // ask "the system" about the path
    error_code err {does_directory_exist(dn.first)};
    if (err) {
        // err != 0 means error
        if (err == errc::permission_denied) {
            // ...
        }
        else if (err == errc::not_a_directory) {
            // ...
        }
        // can't do anything locally
        throw system_error(err);
    }
    // ...
    return ofstream{path};
}


// section 30.4.3.2: error categories
class error_category {
public:
    // ... interface to specific categories derived from error_category ...
};


// section 30.4.3.3: exception system_error
class system_error : public runtime_error {
public:
    // ...
};

try {
    // ... something ...
}
catch (system_error& err) {
    // error message
    cout << "caught system_error " << err.what() << '\n';
    auto ec = err.code();
    cout << "category: " << ec.category().what() << '\n';
    cout << "value: " << ec.value() << '\n';
    cout << "message: " << ec.message() << '\n';
}


// section 30.4.3.4 : potentially portable error conditions
// potentially portable
class error_condition {
public:
    // like error_code but
    // no output operator and
    // no default_error_condition()
};


// section 30.4.3.5: mapping error codes
enum class future_errc {
    broken_promise = 1,
    future_already_retrieved,
    promise_already_satisfied,
    no_state
};

// to be returned from future_category()
class future_cat : error_category {
public:
    const char* name() const noexcept override { return "future"; }
    string message(int ec) const override;
};

const error_category& future_category() noexcept
{
    static future_cat obj;
    return &obj;
}

string future_cat::message(int ec) const
{
    switch (ec) {
        default:
            return "bad future_error code";
        future_errc::broken_promise:
            return "future_error: broken";
        future_errc::future_already_retrieved:
            return "future_error: future already retrieved";
        future_errc::promise_alrready_satisfied:
            return "future_error: promise already satisfied";
        future_errc::no_state:
            return "future_error: no state";
    }
}


error_code make_error_code(future_errc e) noexcept
{
    return error_code{int(e), future_category()};
}

// error
error_code ec1 {7};
// ok
error_code ec2 {future_errc::no_state};
// error
ec1 = 9;
// ok
ec2 = future_errc::promise_already_satisfied;
// error: wrong error category
ec2 = errc::broken_pipe;


template<>
struct is_error_code_enum<future_errc> : public true_type { };

template<typename>
struct is_error_code_enum : pulic false_type { };

error_condition make_error_condition(future_errc e) noexcept;

template<>
struct is_error_condition_enum<future_errc> : public true_type { };


// section 30.4.3.6 : errc error codes
void problem(errc e)
{
    // error: no conversion of errc to int
    if (e == EPIPE) {
        // ...
    }

    // error: broken_pipe not in scope
    if (e == broken_pipe) {
        // ...
    }

    // ok
    if (e == errc::broken_pipe) {
        // ...
    }
}


// section 30.4.3.7: future_errc
// section 30.4.3.8: is_errc error codes standard
