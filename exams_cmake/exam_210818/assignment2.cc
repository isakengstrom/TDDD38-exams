#include <type_traits>

int main()
{
    static_assert(std::is_same_v<uncommon_type<int, double>::type, int>);
    static_assert(std::is_same_v<uncommon_type<int, int>::type, int>);
    static_assert(std::is_same_v<uncommon_type<float, double>::type, float>);
}
