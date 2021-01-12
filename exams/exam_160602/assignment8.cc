#include <iostream>
using namespace std;


void sort(int* begin, int* end)
{
    for ( ; begin +1 != end; ++begin)
    {
        int* min = begin;
        for (int* pos = begin + 1; pos != end; ++pos)
            if (*pos < *min)
                min = pos;
        std::iter_swap(begin, min);
    }
}

int main()
{
    int arr[] = {2,3,5,1,6,8};
    ::sort(begin(arr), end(arr));
    bool first {true};
    for ( auto i : arr )
    {
        if ( !first )
            cout << ", ";
        first = false;
        cout << i;
    }
    cout << endl;

    /*
    vector<int> values {2,3,6,8,3};
    Sort<int, Ascending>::sort(begin(values), end(values));

    list<string> words {"hi", "hello", "all", "students"};
    Sort<string, Descending>::sort(begin(words), end(words));
    */
}
