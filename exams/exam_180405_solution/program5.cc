#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>
#include <iostream>
#include <utility>
#include <cmath>
#include <iomanip>

using namespace std;

double calculate (double k)
{
    double const factor { 8.0 * k };
    double const initial { 4.0 / (factor + 1) - 1.0 / (factor + 4) };

    vector<double> inner_terms { 4.0, 5.0, 6.0 };

    transform (begin (inner_terms), end (inner_terms), begin (inner_terms),
	           [factor](double n)
               {
                  return (-1.0 / (factor + n));
               });

    return accumulate (begin (inner_terms), end (inner_terms), initial);
}

int main ()
{
    int n;
    cin >> n;

    vector <double> term (n);
    iota (begin (term), end (term), 0);

    vector <double> weight { term };

    transform (begin (term), end (term), begin (term), calculate);

    transform (begin (weight), end (weight), begin (weight),
	       [] (double k)
	       {
              return pow (16.0, -k);
	       });

    cout << setprecision (10)
         << inner_product (begin (term), end (term), begin (weight), 0.0)
         << endl;
}
