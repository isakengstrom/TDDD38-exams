#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

template <typename T, class Policy>
class Wrapper
{
public:
    Wrapper(const T t) : value_{t} {}      // initialize value_
    void set(const T t){ value_ = t;}     // set value_
    T get() const {return value_; }         // access value_
    std::string str() const; // string representation of value_
private:
    T value_;
};

template<typename T, class Policy>
std::string Wrapper<T,Policy>::str() const
{
    return Policy::convert(value_);
}

struct Hexadecimal
{
    template <typename T>
    static std::string convert(T const & value)
    {
        ostringstream oss;
        oss << hex << "0x" << value;
        return oss.str();
    }
};

struct Quoted
{
    template <typename T>
    static std::string convert(T const & value)
    {
        ostringstream oss;
        oss << '"' << value << '"';
        return oss.str();
    }
};

int main()
{
    Wrapper<int, Hexadecimal> hexint{4711};
    cout << hexint.str() << endl;

    Wrapper<int, Quoted> citint{4711};
    cout << citint.str() << endl;

    Wrapper<string, Quoted> citstring{"foobar"};
    cout << citstring.str() << endl;

}
