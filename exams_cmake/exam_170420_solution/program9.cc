/*
 * program9.cc
 */
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>

template <typename T, class Order = std::less<T>>
class Ordered_Vector : private std::vector<T>
{
    using parent = std::vector<T>;
public:
    // compiler generated special member functions are ok
    using parent::const_iterator;

    using parent::size;
    using parent::empty;
    using parent::clear;
    using parent::cbegin;
    using parent::cend;
    T const & operator[](size_t idx) const
    {
        return parent::operator[](idx);
    }
    auto begin() const
    {
        return parent::begin();
    }
    auto end() const
    {
        return parent::end();
    }

    void insert(T val)
    {
        auto pos = lower_bound(begin(), end(), val, Order{});
        parent::insert(pos, std::move(val));
    }
};
int main()
{
    using namespace std;

    Ordered_Vector<int, std::greater<int>> v1;

    // cout << v1.front();  // Not allowed to access, as many other vector members

    if (v1.empty())
        cout << "v1 is empty.\n";
    else
        cout << "v1 is not empty.\n";

    v1.insert(5);
    v1.insert(2);
    v1.insert(8);
    v1.insert(3);
    v1.insert(4);
    v1.insert(1);
    v1.insert(9);
    cout << "7 values inserted into v1.\n";
    cout << "v1.size() = " << v1.size() << '\n';
    cout << "v1: ";
    for (unsigned i = 0; i < v1.size(); ++i)
    {
        cout << v1[i] << ' ';  // indexing
    }
    cout << '\n';

    cout << "v2 is copy initialized from v1\n";
    Ordered_Vector<int, std::greater<int>> v2{v1};

    cout << "v2: ";
    copy(begin(v2), end(v2), std::ostream_iterator<int>{cout, " "});
    cout << '\n';
    cout << "v1: ";
    copy(begin(v1), end(v1), std::ostream_iterator<int>{cout, " "});
    cout << '\n';

    cout << "v2 is cleared\n";
    v2.clear();
    cout << "v2.size() = " << v2.size() << '\n';

    cout << "v2 is assigned from v1.\n";
    v2 = v1;
    cout << "v2: ";
    for (auto x : v2)
    {
        cout << x << ' ';
    }
    cout << '\n';
    cout << "v1: ";
    copy(begin(v1), end(v1), std::ostream_iterator<int>{cout, " "});
    cout << '\n';

    return 0;
}
