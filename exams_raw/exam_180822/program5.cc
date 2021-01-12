#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <cassert>

using namespace std;

template <typename T>
T prompt(std::istream& is)
{
    T result;
    is >> result;
    return result;
}

// Should compile and give no output if everything is correct.
int main()
{
    {
        istringstream iss{"57"};
        auto val = prompt<int>(iss);
        assert(val == 57);
    }
    {
        istringstream iss{"3.141592"};
        auto val = prompt<double>(iss);
        assert(val == 3.141592);
    }
    {
        istringstream iss{"this is a test"};
        auto val = prompt<string>(iss);
        assert(val == "this is a test");
    }
    {
        vector<int> result{1, 2, 3, 4, 5};
        istringstream iss{"1 2 3 4 5"};
        auto val = prompt<vector<int>>(iss);
        assert(val == result);
    }
    {
        list<string> result{"this", "is", "a", "test"};
        istringstream iss{"this is a test"};
        auto val = prompt<list<string>>(iss);
        assert(val == result);
    }
}
