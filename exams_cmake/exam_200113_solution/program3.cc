#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
    double const length {10.0};
    vector<double> road {};

    copy(istream_iterator<double>{cin},
         istream_iterator<double>{},
         back_inserter(road));
    
    vector<double> result(road);

    rotate(begin(road), next(begin(road)), end(road));
    
    transform(begin(road), end(road), begin(result), begin(result),
              [length](double a, double b)
              {
                  return sqrt((a - b) * (a - b) + length * length);
              });

    copy(begin(result), end(result), ostream_iterator<double>(cout, " m\n"));
    cout << "Total distance: " << accumulate(begin(result), end(result), 0.0)
         << " m" << endl;
}
