/**************************************************************
* Name     :  ex20-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月26日
**************************************************************/



/*
example 20.2 : derived classes
*/


struct Employee {
    string first_name, family_name;
    char middle_initial;
    Date hiring_date;
    short department;
    // ...
};

// also an Employee
struct Manager {
    // manager's employee record
    Employee emp;
    // people managed
    list<Employee*> group;
    short level;
    // ...
};

// devied class
struct Manager : public Employee {
    list<Employ*> group;
    short level;
    // ...
};


void f(Manager m1, Employee e1)
{
    list<Employee*> elist {&m1, &e1};
    // ...
}

void g(Manager mm, Employee)
{
    // ok : every Manager is an Employee
    Employee* pe = &mm;
    // error : not every Employee is a Manager
    Manager* pm = &ee;
    // disaster : ee doesn't have a level
    pm->level = 2;
    // brute force : works because pe points
    // to the Manager mm
    pm = static_cast<Manager*>(pe);
    // fine : pm points to the Manager mm that has a level
    pm->level = 2;
}

// declaration only, not definition
class Employee;

// error : Employee not defined
class Manager : public Employee {
    // ...
};



// section 20.2.1 : member functions
class Employee {
public :
    void print() const;
    string full_name() const
    {
        return first_name + '' + middle_initial + ' ' + family_name;
    }
    // ...
private :
    string first_name, family_name;
    char middle_initial;
    // ...
};


class Manager : public Employee {
public :
    void print() const;
    // ...
};

void Manager::print() const
{
    cout << "name is " << full_name() << '\n';
    // ...
}

void Manager::print() const
{
    // error!
    cout << "name is " << family_name << '\n';
    // ...
}


void Manager::print() const
{
    // print Employee information
    Employee::print();
    // print Manager-pecific information
    cout << level;
    // ...
}

void Manager::print() const
{
    // oops !
    // print Manager-specific information
    print();
}



// section 20.2.2 : constructor and desturctors
