#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

double calculate(double k)
{
    double const factor{8.0 * k};
    double const initial{4.0 / (factor + 1.0) - 1.0 / (factor + 4.0)};

    vector<double> inner_terms{4.0, 5.0, 6.0};

    for (size_t i{0}; i < inner_terms.size(); ++i)
    {
        inner_terms[i] = -1.0 / (factor + inner_terms[i]);
    }

    double result{initial};
    for (size_t i{0}; i < inner_terms.size(); ++i)
    {
        result += inner_terms[i];
    }

    return result;
}

int main()
{
    int n;
    cin >> n;

    vector<double> terms;

    for (int i{0}; i < n; ++i)
    {
        terms.push_back(i);
    }

    vector<double> weight{terms};

    for (size_t i{0}; i < terms.size(); ++i)
    {
        terms[i] = calculate(terms[i]);
    }

    for (size_t i{0}; i < terms.size(); ++i)
    {
        weight[i] = pow(16.0, -weight[i]);
    }

    double result{0.0};
    for (int i{0}; i < terms.size(); ++i)
    {
        result += terms[i] * weight[i];
    }

    cout << setprecision(10) << std::fixed << result << endl;
}
