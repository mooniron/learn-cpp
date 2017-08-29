/**************************************************************
* Name     :  ex4-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月18日
**************************************************************/


/*
example 4.2 : strings
*/

// concatenation
string compose(const string& name, const string& domain)
{
    return name + '@' + domain;
}

// dmr@bell-labs.com
auto addr = compose("dmr", "bell-labs.com");


// append newline to s1 and s2
void m2(string& s1, string& s2)
{
    // append newline
    s1 = s1 + '\n';
    // append newline, possibly more efficient
    s2 += '\n';
}


// substring amd subscripting
string name = "Niels Stroustrup";

void m3()
{
    // s = "Stroustrup"
    string s = name.substr(6, 10);
    // name becomes "nicholas Stroustrup"
    name.replace(0, 5, "nicholas");
    // name becomes "Nicholas Stroustrup"
    name[0] = toupper(name[0]);
}


// string compare
string incantation;

void respond(const string& answer)
{
    if (answer == incantation) {
        // perform magic
    }
    else if (answer == "yes") {
        // ...
    }
    // ...
}

