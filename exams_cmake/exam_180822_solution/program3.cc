#include <iterator>
#include <utility> // for std::declval
#include <functional> // for std::plus
#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <string>

template <typename iterator, typename bin_op = std::plus<typename iterator::value_type>>
class fold_iterator
{
public:

    using iterator_category = std::forward_iterator_tag;
    using value_type = typename iterator::value_type;
    using difference_type = void;
    using pointer = void;
    using reference = value_type;

    fold_iterator() = default;

    value_type operator*()
    {
        return op(result, *it);
    }
    
    fold_iterator<iterator, bin_op>& operator++()
    {
        result = op(result, *it++);
        return *this;
    }

    fold_iterator<iterator, bin_op> operator++(int)
    {
        auto tmp{*this};
        ++*this;
        return tmp;
    }

    bool operator==(fold_iterator<iterator, bin_op> const& other) const
    {
        return it == other.it;
    }

    bool operator!=(fold_iterator<iterator, bin_op> const& other) const
    {
        return !(*this == other);
    }
        
    
private:

    fold_iterator(iterator it, value_type initial, bin_op op)
        : it{it}, result{initial}, op{op}
    {}
    
    iterator it{};
    value_type result{};
    bin_op op{};

    template <typename container, typename op>
    friend class fold;
};
    

template <typename container, typename bin_op = std::plus<typename container::value_type>>
class fold
{

    using iterator = decltype(std::begin(std::declval<container>()));
    using value_type = typename iterator::value_type;
    
public:

    fold(container& c, value_type initial = {}, bin_op op = {})
        : first{std::begin(c), initial, op}, last{std::end(c), initial, op}
    {}

    fold_iterator<iterator, bin_op> begin() { return first; }
    fold_iterator<iterator, bin_op> end() { return last; }
    
private:

    fold_iterator<iterator, bin_op> first, last;
    
};

using namespace std;

int main()
{
    {
        vector<double> vals { 1.0, 1.1, 0.04, 0.0005, 1.001 };
        cout << "vector<double>: ";
        for (auto res : fold(vals))
            cout << res << ", ";
        cout << endl;
    }

    {
        vector<int> vals { 5, 3, 1, 0, 1 };
        cout << "vector<int>: ";
        for (auto res : fold(vals, 10, minus<int>{}))
            cout << res << ", ";
        cout << endl;
    }

    {
        list<string> vals { "du", " hast", " mich" };
        cout << "list<string>: ";
        for (auto res : fold(vals))
            cout << res << ", ";
        cout << endl;
    }

    {
        deque<pair<int, int>> vals { {1, 1}, {5, 2}, {2, 5}, {2, 1}, {0, 1} };
        cout << "deque<pair<int,int>>: ";
        for (auto res : fold(vals, pair<int, int>{0, 0},
                    [](auto a, auto b)
                    {
                        return pair<int, int>{a.first + b.first, a.second + b.second};
                    }
                 ))
            cout << "(" << res.first << ", " << res.second << "), ";
        cout << endl;
    }

    {
        deque<int> vals {};
        cout << "deque<int>: ";
        for (auto res : fold(vals))
            cout << res << ", ";
        cout << endl;
    }
}
