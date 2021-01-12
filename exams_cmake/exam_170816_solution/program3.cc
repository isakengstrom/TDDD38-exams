#include <forward_list>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename It, typename Comparison = std::less<typename It::value_type>>
void ssort(It start, It end, Comparison comp = {})
{
    for (It cur{start}; cur != end; ++cur )
    {
        auto pos = min_element(cur, end, comp);
        iter_swap(cur, pos);
    }
}

int main()
{
    vector<int> vals {3,21,5,8,0,4,2,67};
    ssort(begin(vals), end(vals));
    for ( auto i : vals )
    {
        cout << i << endl;
    }
    forward_list<string> lst {"hello", "this", "is", "a", "test"};
    ssort(begin(lst), end(lst),
      [](string a, string b){ return a.length() < b.length();});
 }
