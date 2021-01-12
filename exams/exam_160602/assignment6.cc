#include <stdexcept>
#include <iostream>
using namespace std;

int main()
{
    Modular<int, 2, 10> m{3};
    cout << m << endl;
    try
    {
        m = 1;
    }
    catch ( std::domain_error const & e)
    {
        cout << e.what() << endl;
    }
    Modular<int, 2,10> m2 {5};
    m = m + m2;
    cout << m << endl;
    m = m + Modular<int,-11,-2>{-10};
    cout << "Should be 7: " << m << endl;
    cout << "Should print 7 9: " << m++ << " ";
    cout << ++m;
    Modular<char,'a','c'> mc{'b'};
    ++mc;
    cout << "\nShould print a: " << ++mc << endl;
}
