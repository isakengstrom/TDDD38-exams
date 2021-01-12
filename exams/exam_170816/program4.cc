#include <vector>
#include <iostream>
#include <iomanip>

// Main function. The output should be
// true
// false
// true
// false
int main()
{
    std::vector<int> vals {0,0,0,1};
    auto b { begin(vals) };
    auto e { end(vals) };
    using namespace std;
    cout << boolalpha
         << logic_combine(b,e, AtLeast{1}) << '\n'
         << logic_combine(b,e, AtLeast{8}) << '\n'
         << logic_combine(b,e, Any{}) << '\n'
         << logic_combine(b,e) << '\n';
}
