int main()
{
    static_assert(Is_Set<int, float>::value);
    static_assert(!Is_Set<int, int, bool>::value);
    static_assert(!Is_Set<float, int, bool, float>::value);
}