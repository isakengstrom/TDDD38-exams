#include <algorithm>
#include <cassert>
#include <iterator>
#include <map>
#include <vector>
#include <list>

int main()
{
    std::map<int, int> m { {1, 2}, {5, 6} };
    *sorted_inserter(m)++ = std::make_pair(3, 4);
    assert((m == std::map<int, int>{{1,2},{3,4},{5,6}}));

    std::list<std::string> lst { "c" };
    *sorted_inserter(lst)++ = "a";
    *sorted_inserter(lst)++ = "b";
    *sorted_inserter(lst)++ = "a";
    assert((lst == std::list<std::string>{"a", "a", "b", "c"}));

    std::vector<int> v { 5, 7, 3, 12, -5 };

    {
        std::vector<int> res {};
        copy(std::begin(v), std::end(v), sorted_inserter(res));
    
        assert((res == std::vector<int>{-5, 3, 5, 7, 12 }));
    }

    {
        std::vector<int> res {};
        copy(std::begin(v), std::end(v),
             sorted_inserter(res, std::greater<int>{}));
        
        assert((res == std::vector<int>{12, 7, 5, 3, -5}));
    }

    {
        std::vector<int> res {};
        copy(std::begin(v), std::end(v),
             sorted_inserter<std::vector<int>, std::greater<int>>(res));
        assert((res == std::vector<int>{12, 7, 5, 3, -5}));
    }
}
