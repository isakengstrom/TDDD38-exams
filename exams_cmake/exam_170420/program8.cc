/*
 * program8.cc
 */
#include <iostream>
#include <iomanip>
using namespace std;

// Add and modify stuff according to given specifications. 

class Number
{
public:
    Number(double value = 0.0) : value_(value) {}

    int  get_value() const { return value_; }
    void set_value(double value) { value_ = value; }

private:
    int value_;
};

void test_rounding(double value)
{
    // One object for each of the three rounding policies:
    static Number n1;
    static Number n2;
    static Number n3;

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
