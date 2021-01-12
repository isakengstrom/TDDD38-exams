#include <vector>
#include <map>
#include <iterator>
#include <cassert>
#include <list>
#include <iostream>

template <typename Container>
struct Linear
{
    using iterator = decltype(std::begin(std::declval<Container>()));
    
    auto first(Container const & container)
    {
        return std::begin (container);
    }
    
    bool done(Container const & container, iterator it)
    {
        return it != std::end (container);
    }

    auto next(iterator it)
    {
        return ++it;
    }

    template <typename T>
    bool compare(iterator it, T const & target)
    {
        return *it == target;
    }
};

template <typename Container>
class Binary
{
public:
    using iterator = decltype(std::begin(std::declval<Container>()));
    
    auto first(Container const & container)
    {
        left = std::begin (container);
        right = std::end (container);
        return left + std::distance(left, right) / 2;
    }
    
    bool done(Container const & container, iterator it)
    {
        return left != right;
    }

    auto next(iterator it)
    {
        return left + std::distance (left, right) / 2;
    }

    template <typename T>
    bool compare(iterator it, T const & target)
    {
        if (*it > target)
            right = it;
        else if (*it < target)
            left = it + 1;
        else
            return true;
        return false;
    }
private:
    
    iterator left, right;
    
};

// perhaps restructure for template-template
template <typename Container,
          typename T,
          typename Policy = Linear<Container>>
auto sorted_search (Container const & container,
                    T target,
                    Policy policy = Policy{})
{
    auto it { policy.first(container) };
    for (; policy.done(container, it); it = policy.next(it))
    {
        if (policy.compare (it, target))
            return it;
    }
    return std::end(container);
}

int main()
{

    {
        std::list<int> v { 1, 2, 5, 7, 11, 15 };
        assert (*sorted_search (v, 5) == 5);
        assert (*sorted_search (v, 1) == 1);
        assert (sorted_search (v, 6) == std::end(v));
        assert (*sorted_search (v, 15) == 15);
        assert (sorted_search (v, 100) == std::end (v));
    }

    {
        std::vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
        Binary<std::vector<int>> policy{};
        assert (*sorted_search(v, 6, policy) == 6);
        assert (*sorted_search(v, 3, policy) == 3);
        assert (*sorted_search(v, 9, policy) == 9);
        assert (*sorted_search(v, 1, policy) == 1);
        assert (*sorted_search(v, 11, policy) == 11);
        assert (sorted_search(v, 13,  policy) == std::end (v));
    }
}
