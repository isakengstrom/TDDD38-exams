#include <iomanip>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

// Uses data1.txt

int main()
{
    // 1
    vector<int> values { istream_iterator<int>{cin},
                         istream_iterator<int>{} };
    // 2
    cout << values.size() << " values read.\n";
    copy(begin(values), end(values), ostream_iterator<int>{cout, " "});
    
    //3
    sort(begin(values), end(values), std::greater<int>{});

    //4
    values.erase(unique(begin(values), end(values)), end(values));

    //5
     cout << "\nUnique values in descending order:\n";
    copy(begin(values), end(values), ostream_iterator<int>{cout, " "});
    
    //6
    int num = 0.05 * values.size();

    //7
    values.erase(begin(values), begin(values) + num);
    values.erase(end(values) - num, end(values));
    cout << "\nSmallest and largest values removed.\n";
    copy(begin(values), end(values), ostream_iterator<int>{cout, " "});

    //8 (important to have the correct type
    auto mean { accumulate(begin(values), end(values), 0.0) / values.size() };
    cout << "\nMean value: " << setprecision(1) << fixed << mean << endl;

    //9
    auto sum { accumulate(begin(values), end(values),0.0, [mean](double s,auto v){return s+abs(v-mean);}) };
    cout << "Sum of differences: " << sum;
}
