#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

template <typename Iter>
class Enumerate_Iterator
{
public:

    using value_type = std::pair<size_t, typename Iter::value_type>;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    struct DataProxy
    {
        std::pair<size_t const, typename Iter::value_type &> value;
        auto operator->() const
        {
            return &value;
        }
    };
    using pointer = DataProxy *;
    using reference = std::add_lvalue_reference_t<value_type>;

    Enumerate_Iterator(Iter it) : it{it}
    {
    }
    Enumerate_Iterator & operator++()
    {
        ++idx;
        ++it;
        return *this;
    }
    value_type operator*() const
    {
        return {idx, *it};
    }

    bool operator==(Enumerate_Iterator const & rhs) const
    {
        return it == rhs.it;
    }
    bool operator!=(Enumerate_Iterator const & rhs)const
    {
        return !(*this == rhs);
    }
    auto operator->() const
    {
        return DataProxy{{idx, *it}};
    }
private:
    Enumerate_Iterator(Iter it, size_t idx): idx{idx}, it{it} {}
    size_t idx{};
    Iter it;
};


template <typename Container>
class enumerate
{
public:

    using iterator = Enumerate_Iterator<typename Container::iterator>;
    enumerate(Container & c) : c{c} {}
    iterator begin() const
    {
        return std::begin(c);
    }
    iterator end() const
    {
        return std::end(c);
    }
private:
    Container & c;
};
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

