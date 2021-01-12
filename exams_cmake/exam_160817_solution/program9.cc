#include <iostream>
#include <vector>
#include <list>
using namespace std;
template <typename T, typename Container = std::vector<T>>
class Cycler
{
public:
    Cycler(Container & c)
        : cont{c}, current{c.begin()}
    {}
    T & next()
    {
        T & val = *current;
        if ( ++current == cont.end() )
        {
            current = cont.begin();
        }
        return val;
    }
    void reset()
    {
        current = cont.begin();
    }

    typename Container::size_type size() const
    {
        return cont.size();
    }

private:
    Container & cont;
    decltype(cont.begin()) current; // or Container::iterator
};

// Tries both vector<int> and other container with other type
int main()
{
    vector<int> vals {1,4,2,67};
    Cycler<int> c1{vals};
    for (int i{}; i < 10; ++i)
    {
        cout << c1.next() << endl;
    }
   list<string> vals2 {"hi", "hello", "foo"};
    Cycler<string, list<string>> c2{vals2};
    for (int i{}; i < 10; ++i)
    {
        cout << c2.next() << endl;
    }
}
