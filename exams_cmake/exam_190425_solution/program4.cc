#include <cstddef>
#include <utility>
#include <iterator>

template <typename T>
auto get_size(T&& t);

template <typename T>
auto get_size_helper(T&& t, int)
    -> decltype(std::begin(t), t.size())
{
    int total{};
    for (auto&& e : t)
        total += get_size(e);
    return total;
}

template <typename T>
auto get_size_helper(T&& t, float)
{
    return sizeof(t);
}

template <typename T>
auto get_size(T&& t)
{
    return get_size_helper(std::forward<T>(t), 0);
}

template <typename... Args>
std::size_t total_size(Args&&... args)
{
    return (get_size(std::forward<Args>(args)) + ... + 0);
}

#include <vector>
#include <string>
#include <set>
#include <list>
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    int x{};
    assert(get_size(x) == 4);

    assert(total_size(x) == 4);
    
    int arr[3] {1, 2, 3};
    assert(get_size(arr) == 12);
    assert(total_size(x, arr) == 16);
    
    string str {"this is a test"};
    assert(get_size(str) == 14);

    assert(total_size(x, arr, str) == 30);
    
    vector<string> v {"hello", "there are some characters", "in here"};
    assert(get_size(v.front()) == 5);

    assert(total_size(x, arr, str, v.front()) == 35);
    
    assert(get_size(v) == 37);

    assert(total_size(x, arr, str, v.front(), v) == 72);
    
    set<list<int>> s { {1, 2, 3}, {4, 5}, {6} };
    assert(get_size(s) == 24);

    assert(total_size(x, arr, str, v.front(), v, s) == 96);
}
