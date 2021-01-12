#include "Timer.h"
#include <iostream>
#include <thread>
#include <utility>
#include <chrono>
using namespace std;

template <typename Fun>
class Profiler
{
public:
    Profiler(Fun && f): fun{forward<Fun>(f)} {}
    Profiler() = default;
    template <typename ...Args, typename Ret=invoke_result_t<Fun, Args...>>
    auto operator()(Args && ...args) -> enable_if_t<is_same_v<Ret, void>>
    {
        timer.reset();
        fun(std::forward<Args>(args)...);
        total_time += timer.reset();
        ++call_count;
    }
    template <typename ...Args, typename Ret=invoke_result_t<Fun, Args...>>
    auto operator()(Args && ...args) -> enable_if_t<!is_same_v<Ret, void>, Ret>
    {
        timer.reset();
        Ret ret { fun(std::forward<Args>(args)...) };
        total_time += timer.reset();
        ++call_count;
        return ret;
    }
    size_t calls() const
    {
        return call_count;
    }
    Timer::milliseconds mean() const
    {
        return total_time / call_count;
    }

private:
    Fun fun {};
    Timer timer{};
    Timer::milliseconds total_time {};
    size_t call_count {};
};

class Fun
{
public:
    void operator()(){ std::cout << "Hello"; }
};

int main()
{
    // for 2 points
    Profiler<Fun> f;
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

