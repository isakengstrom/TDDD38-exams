#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
    int N,T;
    cin >> N >> T;                                                     // 1
    vector<int> input_values (N);                                      // 2
    copy_n(istream_iterator<int>{cin}, N, begin(input_values));        // 3
    vector<int> sums (N);                                              // 4
    partial_sum(begin(input_values), end(input_values), begin(sums));  // 5
    for_each(istream_iterator<int>{cin}, istream_iterator<int>{},
            [=](int t){cout << sums[t-1] << endl; });                  // 6

    return 0;
}
