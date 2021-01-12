#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>

using namespace std;

vector<string> serialize(vector</* Printable */> const& v)
{
  vector<string> result{};
  for (/* Printable */ obj : v)
  {
    if (/* Check if obj is a Serializable */)
    {
      result.push_back(/* Call serialize on obj */);
    }
  }
  return result;
}

void print(ostream& os, vector</* Printable */> const& v)
{
  for (/* Printable */ obj : v)
  {
    /* Call print on obj with os as parameter */
    os << endl;
  }
}

int main()
{
  vector</* Printable */> v = {
    // Message{"Hello there"},
    // Integer{0},
    // Message{"This is a message"},
    // Integer{100053},
    // Integer{-5}
  };

  {
    vector<string> result {serialize(v)};
    assert((result == vector<string>{"0", "100053", "-5"}));
  }
  
  {
    ostringstream oss{};
    print(oss, v);
    assert(oss.str() == "Hello there\n0\nThis is a message\n100053\n-5\n");
  }

  {
    Integer i{0};
    assert(i.deserialize("15"));
    assert(i.serialize() == "15");
  }
  
}
