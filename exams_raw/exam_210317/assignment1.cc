#include <algorithm>
#include <random>
#include <iterator>
#include <vector>
#include <iostream>
#include <string>
#include <list>

std::mt19937 gen { std::random_device{}() };

// Implement your solution here

// Inspiration for the operators:

// operator*() {
//     return *(container.begin() + left.back()); // use std::next instead
// };

// operator++() {
//     left.pop_back();
//     return *this;
// }

// Where 'left' initially contains all numbers from 0 up to (but not
// including) the size of the container. 'left' should then be
// shuffled in the constructor of random_iterator. This guarantees
// that each element is visited exactly once, but in a random order.

int main()
{

    std::cout << "==== vector ====" << std::endl;
    
    std::vector<int> v { 1, 3, 5, 7, 9, 11, 13 };    
    for (int i : shuffled(v))
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "==== list ====" << std::endl;
    
    std::list<std::string> l { "a", "bc", "d", "efg", "hijklm" };
    for (std::string s : shuffled(l))
    {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}
