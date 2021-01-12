#include <cassert>

int start(int x, int y)
{
    return x + y;
}

double step(int x)
{
    return 0.5 * x;
}

int last(double x)
{
    return x;
}

int main()
{
    {
        int x{};
        auto f = call_chain(start, step, last);
        assert(f(x, x) == 0);

        x = 1;

        assert(f(x, x) == 1);
        
        assert(f(1, 4) == 2);
        assert(f(3, 3) == 3);
    }

    {
        auto f = call_chain([](int x = 1, int y = 1, int z = 1) { return x * (y + z); },
                            [](int x) { return x * x; },
                            [](int x) { return x - 1; });

        assert(f() == 3);
        assert(f(2) == 15);
        assert(f(2, 3) == 63);
        assert(f(2, 3, 4) == 195);
    }

    {
        auto f = call_chain(call_chain([]() { return 1; },
                                       [](int x) { return x + 1; }),
                            [](int x) { return x * x; });

        assert(f() == 4);
    }
}
