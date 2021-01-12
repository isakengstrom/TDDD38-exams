#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

struct Ascending
{
    template <typename T>
    static bool less(T const & lhs, T const & rhs)
    {
        return lhs < rhs;
    }
};

struct Descending
{
    template <typename T>
    static bool less(T const & lhs, T const & rhs)
    {
        return lhs != rhs && rhs < lhs;
    }
};

template <typename T, class Order_Policy=Ascending>
struct Sort
{
    template <typename Iter>
    static void sort(Iter begin, Iter end)
    {
        for ( ; next(begin) != end; ++begin)
        {
            Iter min = begin;
            for (Iter pos = next(begin); pos != end; ++pos)
                if ( Order_Policy::less(*pos, *min) )
                    min = pos;
            std::iter_swap(begin, min);
        }
    }
};

// a general print function to see that the sorting works.
// This was not required.
template <typename Cont>
void print(Cont const & arr)
{
    bool first {true};
    for ( auto i : arr )
    {
        if ( !first )
            cout << ", ";
        first = false;
        cout << i;
    }
    cout << endl;
}
int main()
{
    int arr[] = {2,3,5,1,6,8};
    Sort<int>::sort(begin(arr), end(arr));
    print(arr);

    vector<int> values {2,3,6,8,3};
    Sort<int, Ascending>::sort(begin(values), end(values));
    print(values);

    list<string> words {"hi", "hello", "all", "students"};
    Sort<string, Descending>::sort(begin(words), end(words));
    print(words);
}
