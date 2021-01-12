#include <chrono>
#include <iostream>

class Function
{
public:
    void operator()(){ std::cout << "Hello"; }
};

using namespace std;
int main()
{
    // for 2 points
    Profiler<Function> f;
    Profiler fun { [](){this_thread::sleep_for(chrono::seconds{1}); return 2; } };
    fun();
    fun();
    cout << fun.mean();

    // addition for 3 points
    {
        Profiler fun { [](){this_thread::sleep_for(chrono::seconds{1}); } };
        fun();
        fun();
        cout << fun.mean();
    }
    // addition for 4 points
    {
        Profiler fun { [](int a){this_thread::sleep_for(chrono::seconds{a}); return a; } };
        Profiler fun2 { [](int a, double b){this_thread::sleep_for(chrono::seconds{a}); return b; } };
        fun(2);
        fun(3);
        cout << fun.mean();
    }
    // addition for 5 points
    {
        Profiler fun { [](int && a, int & b){} };
        int c;
        fun(5,c);
        //fun(4,5) or fun(c,5)  should not compile
    }
}

