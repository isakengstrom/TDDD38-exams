#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

int main() {
  {
    // This block should print the following to cout:
    // Hello my
    // name is
    // Eric who
    // are you
    LineWrapper wrapper{8, cout};
    vector<string> words{"hello", "my",  "name", "is",
                         "Eric",  "who", "are",  "you"};
    copy(begin(words), end(words), wrapper);
    cout << endl;
  }
  {
    // The following is expected:
    // 1234
    // 3 5
    // end
    LineWrapper wrapper{3};
    wrapper = 1234;
    wrapper = 3;
    wrapper = 5;
    wrapper = "end";
    cout << endl;
  }
}
