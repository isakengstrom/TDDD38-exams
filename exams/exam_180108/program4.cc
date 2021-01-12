#include <iostream>
#include <vector>
using namespace std;

int main()
{
    std::vector vals {2,3,2,4,6,7};

    for ( auto && [idx,val]: enumerate(vals) )
        cout << idx << ": " << val++ << endl;

    for ( auto i: vals )
        cout << i << ' ';
    cout << endl;

    for (auto [index, value]: enumerate(vals) )
        cout << index << ": " << value << endl;

    Enumerate_Iterator it{begin(vals)};
    cout << '\n' << it->first << ' ' << it->second << '\n';
    ++it;
    cout << it->first;
}
