/**************************************************************
* Name     :  ex12-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月18日
**************************************************************/



/*
example 12.2 : argument passing
    section 12.2.4 : unspecified number of arguments
*/


#include <cstdio>

// from <cstdio>
int fprintf(File*, const char* ...)
// from unix header
int execl(const char* ...);


extern void error(int ...);
extern char* itoa(int, char[]);

int main(int argc, char* argv[])
{
    std::printf("My name is %s %s\n", 2);

    switch (argc) {
        case 1 :
            error(0, argc[0], nullptr);
            break;
        case 2 :
            error(0, argv[0], argv[1], nullptr);
            break;
        default :
            char buffer[8];
            error(1, argv[0], " with ", itoa(argc - 1, buffer), "arguments", nullptr);
    }
    // ...
}


// error() definition
#include <cstdarg>

// "severity" followed by a zero-terminated list of char*s
void error(int severity ...)
{
    va_list ap;
    // arg startup
    va_start(ap, severity);

    for ( ; ; ) {
        char* p = va_arg(ap, char*);
        if (p == nullptr) {
            break;
        }
        cerr << p << ' ';
    }

    // arg cleanup
    va_end(ap);
    cerr << '\n';

    if (severity) {
        exit(severity);
    }
}


// initializer_list version
void error(int severity, initializer_list<string> err)
{
    for (auto& s : err) {
        cerr << s << ' ';
    }

    cerr << '\n';
    if (severity) {
        exit(severity);
    }
}

int main(int argc, char* argv[])
{
    switch (argc) {
        case 1 :
            error(0, {argv[0]});
            break;
        case 2 :
            error(0, {argv[0]}, argv[1]);
            break;
        default :
            error(1, {argv[0], "with", to_string(argc - 1), "arguments"});
            //break;
    }
}


// vector<string> version
// almost as before
void error(int severity, const vector<string>& err)
{
    for (auto& s : err) {
        cerr << s << ' ';
    }

    cerr << '\n';
    if (severity) {
        exit(severity);
    }
}

// package arguments
vector<string> arguments(int argc, char* argv[])
{
    vector<string> res;
    for (int i - 0; i != argc; ++i) {
        res.push_back(argv[i]);
    }
    return res;
}

int main(int argc, char* argv[])
{
    auto grgs = arguments(argc, argv);
    error((args.size() < 3) ? 0 : 1, args);
}
