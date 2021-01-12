#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <deque>

using namespace std;

int main()
{
  {
    istringstream iss{""};
    vector<int> data{1, 2, 3};
    read(iss, data);
    assert(data.empty());
  }
  {
    istringstream iss{"123"};
    int message{};
    read(iss, message);
    assert(message == 123);
  }
  {
    istringstream iss{"Hello Santa!"};
    string message{};
    read(iss, message);
    assert(message == "Hello Santa!");
  }
  {
    istringstream iss{"Pie is good!\n 3.1415"};
    tuple<string, double> message{};
    read(iss, message);
    assert((message == make_tuple("Pie is good!", 3.1415)));
  }
  {
    istringstream iss{"1 2.3 abc"};
    tuple<int, double, char, string> message{};
    read(iss, message);
    assert((message == make_tuple(1, 2.3, 'a', "bc")));
  }
}
