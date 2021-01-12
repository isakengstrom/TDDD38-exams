#include <numeric>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
using namespace std;

int main()
{
    vector<int> vals{istream_iterator<int>{cin}, istream_iterator<int>{}};
    size_t elements { vals.size() };
    size_t mid { elements / 2 };
    nth_element(begin(vals), begin(vals) + mid, end(vals));
    auto sum = accumulate(begin(vals), end(vals), 0.0);
    auto mean { sum / elements };
    auto med { static_cast<double>(vals.at(mid)) };
    if ( elements % 2 == 0 )
    {
        nth_element(begin(vals), begin(vals) + (mid-1), end(vals));
        med = (med + vals.at(mid-1)) / 2;
    }
    double diffs {};
    for_each(begin(vals), end(vals), [&diffs, mean](auto val){ diffs += pow(val-mean, 2.0); });
    auto dev { sqrt( diffs / elements ) };
    auto mm = minmax_element(begin(vals), end(vals));
    cout << setfill('.') << left
         << setw(18) << "min value" << ": " << *mm.first << '\n'
         << setw(18) << "max value" << ": " << *mm.second << '\n' 
         << setw(18) << "mean" << ": " << mean << '\n'
         << setw(18) << "median" << ": " << med << '\n'
         << setw(18) << "standard deviation" << ": " << dev << endl;
}
