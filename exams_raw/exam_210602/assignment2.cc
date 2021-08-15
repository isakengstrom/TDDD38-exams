#include <cassert>
#include <list>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// Looping over two containers of different size:

// auto lhs_it { begin(lhs) };
// auto rhs_it { begin(rhs) };

// while (lhs_it != end(lhs) && rhs_it != end(rhs))
// {
//     ++lhs_it;
//     ++rhs_it;
// }

int main()
{
    {
        vector<int> v { 1, -2, 3 };
        string s { "hello world" };

        auto res = join(v, s);
        assert( (res == vector<pair<int, char>>{ {1, 'h'}, {-2, 'e'}, {3, 'l'} }) );
    }

    {
        list<string> l { "hello", "there" };
        int x { 3 };

        auto left = join(l, x);
        assert( (left == vector<pair<string, int>>{ {"hello", 3}, {"there", 3} }) );

        auto right = join(x, l);
        assert( (right == vector<pair<int, string>>{ {3, "hello"}, {3, "there"} }) );
    }
}