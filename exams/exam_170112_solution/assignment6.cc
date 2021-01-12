// This solution has checks according to the concepts TS. This is
// not required for this question and can be commented out. Can be
// complied with g++-6.1 or later with the flag -fconcepts
#include <type_traits>
#include <iterator>
#include <iostream>
using namespace std;

template <typename T>
requires std::is_arithmetic<T>::value
class Range_Iterator
{
public:
  using iterator_category = std::input_iterator_tag;
  using value_type = T;
  using difference_type = T;
  using pointer = T const *;
  using reference = T;

  explicit Range_Iterator(T val, T step = 1) : cur{val}, step{step} {}
  Range_Iterator &operator++()
  {
    cur += step;
    return *this;
  }
  Range_Iterator operator++(int)
  {
    Range_Iterator tmp{*this};
    ++*this;
    return tmp;
  }
  bool operator==(Range_Iterator const &rhs) const
  {
    return !(*this != rhs);
  }
  bool operator!=(Range_Iterator const &rhs) const
  {
    return (step > 0) ? cur < rhs.cur : cur > rhs.cur;
  }
  reference operator*() const { return cur; }
private:
  T cur, step;
};

template <typename T>
requires std::is_arithmetic<T>::value
class Range
{
public:
  using iterator = Range_Iterator<T>;
  Range(T start, T end, T step = 1)
      : first{start}, last{end}, step{step}
  {
  }
  explicit Range(T end) : Range{T{}, end} {}

  iterator begin() const { return iterator{first, step}; }
  iterator end() const { return iterator{last}; }
private:
  T first, last, step;
};

template <typename T, typename... Extra>
requires std::is_arithmetic<T>::value &&
    (... && std::is_same<T, Extra>::value)
auto range(T val, Extra... vals)
{
  return Range<T>{val, vals...};
}

int main()
{
  {
    // This block should work when everything is finished
    // print values [0,9[
    for (int v : range(10))
    {
      cout << v << ' ';
    }

    // print values 2.3, 2.6, 2.9
    for (auto v : range(2.3, 3.0, 0.3))
    {
      cout << v << ' ';
    }

    // prints 2 1 0 -1 (has a negative step size)
    for (auto v : range(2, -2, -1))
    {
      cout << v << ' ';
    }

    // will not print anything
    for (auto v : range(2, -1, 3))
    {
      cout << v << ' ';
    }
  }

  {
    // This block shows some parts of the Range_Iterator class
    Range_Iterator<int> s{2};
    Range_Iterator<int> e{10};
    while (s != e)
    {
      cout << *s << ' ';
      ++s;
    } // prints 2 3 4 5 6 7 8 9

    // *s = 4; // should not be possible

    Range_Iterator<double> start{2.3, 0.3};
    Range_Iterator<double> stop{3.0};
    while (start != stop)
    {
      cout << *start++ << ' ';
    } // should print 2.3 2.6 2.9
  }
}
