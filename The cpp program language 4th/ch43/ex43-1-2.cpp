/**************************************************************
* Name     :  ex43-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月27日
**************************************************************/



/*
example 43 : the c standard library
*/


// section 43.3: printf() family
int x = 5;
const char* p = "Pedersen";
printf("the value of x is '%d' and the value of s is '%s'\n", x, s)

// against scanf
int x;
char s[buf_size];
int i = scanf("the value of x is '%d' and the value of s is '%s'\n", &x, s);

// veruy dangerous code
char s[buf_size];
// read a line into s
char* p = gets(s);


// section 43.5: memory
int max = 1024;
char* p = static_cast<char*>(malloc(max));
char* current_word = nullptr;
bool in_word = false;
int i = 0;
while (cin.get(&p[i])) {
    if (isletter(p[i])) {
        if (!in_word) {
            current_word = &p[i];
            in_word = true;
        }
    }
    else {
        in_word = false;
    }
    if (++i == max) {
        // double allocation
        p = static_cast<char*>(realloc(p, max *= 2));
    }
    // ...
}


// section 43.6: date and time
struct tm {
    // second of minute [0:61]; 60 and 61 represent leap seconds
    int tm_sec;
    // minute of hour [0:59]
    int tm_min;
    // hour of day [0:23]
    int tm_hour;
    // day of month [1:31]
    int tm_mday;
    // month of year [0:11]
    int tm_mon;
    // year since 1900;
    int tm_year;
    // days since Sunday [0:6]
    int tm_wday;
    // days since January 1 [0:365]
    int tm_yday;
    // hours of daylight savings time
    int tm_isdst;
};

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    clock_t t1 = clock();
    if (t1 == clock_t(-1)) {
        // clock_t(-1) means "clock() didn't work"
        cerr << "sorry, no clock\n"
        exit(1);
    }
    for (int i = 0; i < n; ++i) {
        // timing loop
        do_something();
    }
    clock_t t2 = clock();
    if (t2 == clock_t(-1)) {
        cerr << "sorry, no clock\n"
        exit(2);
    }
    cout << "do_something() " << n << " times took " << double(t2-t1)/CLOCKS_PER_SEC "seconds"
        << "(measurement granularity: " CLOCKS_PER_SEC << "of a second)\n";
}


void almost_C()
{
    const int max = 80;
    char str[max];
    time_t t = time(nullptr);
    tm* pt = localtime(&t);
    strftime(str, max, "%D, %H:%M(%I:%M%p)\n", pt)
    printf(str);
}


// section 43.7: etc.
int (*cmp)(const void* p, const void* q);

// largest signed integer type
typedef long long intmax_t;
// largest unsigned integer type
typedef unsigned long long uintmax_t;

