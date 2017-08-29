/**************************************************************
* Name     :  ex13-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月23日
**************************************************************/



/*
example 13.4 : enforcing invariants
*/


// n should be in [1, max)
void f(int n)
{
    if (2 < debug_level && (n <= 0 || max < n)) {
        throw Assert_error("range problem");
    }
    // ...
}


namespace Assert {
    enum class Mode { throw_, terminate_, ignore_};
    constexpr Mode current_mode = CURRENT_MODE;
    constexpr int current_level = CURRENT_LEVEL;
    constexpr int default_level = 1;

    constexpr bool level(int n)
    {
        return n <= current_level;
    }

    struct Error : runtime_error {
        Error(const string& p) : runtime_error(p) { }
    };

    // ...
    // compose message including file name and line number
    string compose(const char* file, int line, const string& message)
    {
        ostring stream os ("{");
        os << file << ", " << line << "); " << message;
        return os.str();
    }

    template<bool condition = level(default_level), class Except = Error>
    void dynamic(bool assertion, const string& message = "Assert::dynamic failed")
    {
        if (assertion) {
            return;
        }
        if (current_mode == Assert_mode::throw_) {
            throw Except(message);
        }
        if (current_mode == Assert_mode::terminate_) {
            std::terminate();
        }
    }

    // do nothing
    template<>
    void dynamic<false, Error>(bool, const string&)
    {
    }

    // default action
    void dynamic(bool b, const string& s)
    {
        dynamic<true, Error>(b, s);
    }

    // default message
    void dynamic(bool b)
    {
        dynamic<true, Error>(b);
    }
};


// n should be in [1: max)
void f(int n)
{
    Assert::dynamic<Assert::level(2), Assert::Error>(
        (n <= 0 || max < n), Assert::compose(__FILE__, __LINE__, "range problem")
    );
    // ...
    Assert::dynamic((n <= 0 || max < n), Assert::compose(__FILE__, __LINE__, "range problem"));
    // ...
    dynamic(n <= 0 || max < n);
}


