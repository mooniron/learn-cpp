/**************************************************************
* Name     :  ex27-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月18日
**************************************************************/



/*
example 27.4 : template parameters as base classes
*/



// section 27.4.1 : composing data structures
// doesn't know about Val (the user data)
template<typename N>
struct Node_base {
    N* left_child;
    N* right_child;
    Node_base();
    void add_left(N* p)
    {
        if (left_child == nullptr) {
            left_child = p;
        }
        else
        // ...
    }
    // ...
};

// use derived class as part of its own base
template<typename Val>
struct Node : Node_base<Node<Val>> {
    Val v;
    Node(Val vv);
    // ...
};

struct Node_base_double {
    double val;
    Node_base_double* left_child;
    Node_base_double* right_child;
};


using My_node = Node<double>;

void user(const  vector<double>& v)
{
    My_node root;
    int i = 0;

    for (auto x : v) {
        auto p = new My_node{x};
        // choose where to insert
        if (i++ % 2) {
            root.add_left(p);
        }
        else {
            root.add_right(p);
        }
    }
}


// add balancer
template<typename N>
struct Node_base {
    static_assert(Totally_ordered<N>(), "Node_base: N must have a <");
    N* left_child;
    N* right_child;
    Balancing_info bal;
    Node_base();
    void insert(N& n)
    {
        if (n < *left_child) {
            // ... do something ...
        }
        else {
            // ... do something else ...
        }
    }
    // ...
};


template<typename Val, typename Balance>
struct Search_node : public Node_base<Search_node<Val, Balance>, Balance> {
    // user data
    Val val;
    Search_node(Val v) : val(v) {}
};

template<typename N, typename Balance>
struct Node_base : Balance {
    N* left_child;
    N* right_child;
    Node_base();

    void insert(N& n)
    {
        // use compare() from Balance
        if (this->compare(n, left_child)) {
            // ... do something ...
        }
        else {
            // ... do something else ...
        }
    }
    // ...
};


struct Red_black_balance {
    // data and operations needed to implement red-black trees
};

// type alias for red-black trees
template<typename T>
using Rbnode = Search_node<T, Red_black_balance>;

// a red-black tree of doubles
Rbnode<double> my_root;

using My_node = Rb_node<double>;

void user(const vector<double>& v)
{
    for (auto x : v) {
        root.insert(*new My_node{x});
    }
}


template<typename N>
struct Node_base : N::balance_type {
    // use N's balance_type
    // ...
};

template<typename Val, typename Balance>
struct Search_node : public Node_base<Search_node<Val, Balance>> {
    using balance_type = Balance;
    // ...
};


// section 27.4.2 : linearizing class hierarchies
struct ipr::Node {
    const int node_id;
    const Category_code category;
    // hook for visitor classes
    virtual void accept(Visitor&) const = 0;
protected :
    Node(Category_code);
};

struct ipr::Expr : Node {
    virtual const Type& type() const = 0;
protected :
    Expr(Category_code c) : Node(c) { }
};

struct ipr::Stmt : Expr {
    // line in file
    virtual const Unit_location& unit_location() const = 0;
    // file
    virtual const Source_location& source_location() const = 0;
    virtual const Sequence<Annotation>& annotation() const = 0;
protected :
    Stmt(Category_code c) : Expr(c) { }
};

struct ipr::Decl : Stmt {
    // storage class, virtual, access control, etc.
    enum Specifier { /* ... */ };
    virtual Specifier specifiers() const = 0;
    virtual const Linkage& lang_linkage() const = 0;
    virtual const Name& name() const = 0;
    virtual const Region& home_region() const = 0;
    virtual const Region& lexical_region() const = 0;
    virtual bool has_initializer() const = 0;
    virtual const Expr& initializer() const = 0;
    // ...
protected :
    Decl(Category_code c) : Stmt(c) { }
};


struct ipr::Var : Category<var_cat, Decl> {
};

template<Category_code Cat, typename T = Expr>
struct Category : T {
protected :
    Category() : T(Cat) { }
};


template<typename T>
struct impl::Node : T {
    // make the template argument type available to users
    using Interface = T;
    void accept(ipr::Visitor& v) const override
    {
        v.visit(*this);
    }
};

template<typename Interface>
struct impl::Expr : impl::Node<Interface> {
    // constraint is the type of the expression
    const ipr::Type* constraint;
    Expr() : constraint(0) { }
    const ipr::Type& type() const override
    {
        return *util::check(constraint);
    }
};

template<typename S>
struct impl::Stmt : S {
    // logical position in translation unit
    ipr::Unit_location unit_locus;
    // source file, line, and column
    ipr::Source_location src_locus;
    ref_sequence<ipr::Annotation> notes;

    const ipr::Unit_location& unit_location() const override
    {
        return unit_locus;
    }
    const ipr::Source_location& source_location() const override
    {
        return src_locus;
    }
    const ipr::Sequence<ipr::Annotation>& annotation() const override
    {
        return notes;
    }
};

template<typename D>
struct impl::Decl : Stmt<Node<D>> {
    basic_decl_data<D> decl_data;
    ipr::Named_map* pat;
    val_sequence<ipr::Substitution> args;
    Decl() : decl_data(0), pat(0) { }
    const ipr::Sequence<ipr::Substitution>& substitution() const
    {
        return args;
    }
    const ipr::Named_map& generating_map() const override
    {
        return *util::check(pat);
    }
    const ipr::Linkage& lang_linkage() const override;
    const ipr::Region& home_region() const override;
};

struct Var : impl::Decl<ipr::Val> {
    const ipr::Expr* init;
    const ipr::Region* lexreg;
    Var();
    bool has_initializer() const override;
    const ipr::Expr& initializer() const override;
    const ipr::Region& lexical_region() const override;
};

