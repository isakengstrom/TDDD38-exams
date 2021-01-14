#include <vector>
#include <list>
#include <tuple>
#include <cassert>

int main()
{
    std::tuple<int, int, int> t { 0, 1, 2 };
    assert(get<0>(t) == 0);
    assert(get<1>(t) == 1);
    assert(get<2>(t) == 2);

    std::vector<int> v { 3, 2, 1, 0 };
    assert(get<0>(v) == 3);
    assert(get<1>(v) == 2);
    assert(get<2>(v) == 1);
    assert(get<3>(v) == 0);

    std::list<double> l { 1.2, 3.4, 5.6 };
    assert(get<0>(l) == 1.2);
    assert(get<1>(l) == 3.4);
    assert(get<2>(l) == 5.6);

    std::array<std::string, 3> a { "123", "45", "6789" };
    assert(get<0>(a) == "123");
    assert(get<1>(a) == "45");
    assert(get<2>(a) == "6789");

    char c[2] { 'a', 'b' };
    assert(get<0>(c) == 'a');
    assert(get<1>(c) == 'b');
}
