#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
using namespace std;

struct format_container
{
    format_container(char delim='[')
    {
        if (delim == '{')
        {
            start='{';
            end = '}';
        }
    }
    char start{'['}, end{']'};
    mutable ostream * os{};
};


template<typename Container>
ostream & operator<<(format_container const & cp, Container const & vals)
{
    *cp.os << cp.start;
    bool first {true};
    for ( auto && val : vals )
    {
        if ( first )
            first = false;
        else
            *cp.os << ", ";
        *cp.os << val;
    }
    return *cp.os << cp.end;
}

format_container const & operator<<(ostream & os, format_container const & cp)
{
    cp.os = &os;
    return cp;
}

int main()
{
    vector<int> vals {1,5,2,7,9};
    cout << format_container() << vals << endl;
    list<string> lst{"hi", "does", "this", "work?"};
    forward_list<int> fl{3,65,1,8};
    cout << format_container() << lst << "\n"
         << format_container('{') << fl << endl;
}
