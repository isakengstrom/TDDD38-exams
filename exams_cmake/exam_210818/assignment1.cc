#include <cassert>
#include <deque>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// Random number generator, is OK if it is global.
std::mt19937 gen { std::random_device{}() };

// Generating float in range [0.0f, 1.0f]:
// std::uniform_real_distribution<float> dist { 0.0f, 1.0f };
// return dist(gen);

// Generating int in range [0, 10]:
// std::uniform_int_distribution<int> dist { 0, 10 };
// return dist(gen);

int main()
{
    for (int i {0}; i < 1000; ++i)
    {
        assert(( random(10) <= 10 )); // int in rane [0, 10]
        assert(( random(1.0f) <= 1.0f )); // float in range [0.0f, 1.0f]
        assert(( random(0.5) <= 0.5 )); // double in range [0.0, 0.5]
        assert(( random(15u) <= 15u )); // unsigned in range [0u, 15u]
    }

    // shuffle the elements in 'v'
    std::vector<int> v { 1, 2, 3 };
    for (auto i : random(v))
    {
        std::cout << i << std::endl;
    }

    // shuffle the elements in 'd'
    std::deque<float> d { 4.5, 6.7, 8.9, 10.0 };
    for (auto i : random(d))
    {
        std::cout << i << std::endl;
    }

    // shuffle the characters in 's'
    std::string s { "abcdef" };
    std::cout << random(s) << std::endl;
}
