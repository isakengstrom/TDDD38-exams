#include <functional>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>
#include <vector>
using namespace std;

using num_type = unsigned long long;

constexpr bool is_prime(num_type val, num_type divisor=2)
{
    if ( divisor*divisor > val )
    {
        return true;
    }
    if ( val % divisor == 0 )
    {
        return false;
    }
    return is_prime(val, ++divisor);
}

int main()
{
    vector<num_type> vals(10);
    random_device rnd;
    uniform_int_distribution<num_type> dist{2,75};
    generate(begin(vals), end(vals),bind(dist,ref(rnd)));
    vals.erase(remove_if(begin(vals), end(vals),
                         [](num_type val){return !is_prime(val);}),
               end(vals));
    sort(begin(vals), end(vals));
    copy(begin(vals), end(vals), ostream_iterator<num_type>{cout," "});
    cout << accumulate(begin(vals),end(vals),1,multiplies<>{})<<endl;
}
