/*
 * program8_1.cc
 * Templated policy classes with template-template parameter to Number.
 * Allows the user to use Number without instantiating the policy
 */
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

template <typename arg_type, typename ret_type>
struct Round_Up
{
    static ret_type round(arg_type val)
    {
        return ceil(val);
    }
};

template <typename arg_type, typename ret_type>
struct Round_Down
{
    static ret_type round(arg_type val)
    {
        return floor(val);
    }
};

template <typename arg_type, typename ret_type>
struct Round_Towards_Zero
{
    static ret_type round(arg_type val)
    {
        return val < 0 ? ceil(val) : floor(val);
    }
};

template <typename value_type, typename floating_type,
          template <typename, typename> class Rounding_Policy = Round_Towards_Zero>
class Number
{
public:
    Number(floating_type value = 0): value_{round(value)}
    {}

    value_type  get_value() const { return value_; }
    void set_value(floating_type value) { value_ = round(value); }


private:
    value_type value_;
    value_type round(floating_type val) const
    {
        return Rounding_Policy<floating_type, value_type>::round(val);
    }
};

void test_rounding(double value)
{
    // One object for each of the three rounding policies:
    static Number<int, double, Round_Up> n1;
    static Number<int, double, Round_Down> n2;
    static Number<int, double> n3;

    n1.set_value(value);
    n2.set_value(value);
    n3.set_value(value);

    cout << setw(11) << left << value
         << setw(11) << n1.get_value()
         << setw(11) << n2.get_value()
         << setw(11) << n3.get_value()
         << '\n';
}

int main()
{
    cout << fixed << setprecision(2) << showpos;
    cout << setw(11) << left << "Value" 
         << setw(11) << "Down" 
         << setw(11) << "Up" 
         << setw(11) << "Towards 0"
         << "\n\n";

    test_rounding(9.67);
    test_rounding(9.5);
    test_rounding(9.35);
    test_rounding(9.0);
    test_rounding(0.0);
    test_rounding(-9.0);
    test_rounding(-9.25);
    test_rounding(-9.5);
    test_rounding(-9.67);

    return 0;
}
