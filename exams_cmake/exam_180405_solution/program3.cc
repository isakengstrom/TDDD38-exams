// An output iterator usually does nothing in the increment and dereference and does all logic in assignment.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class LineWrapper {
public:
  using iterator_category = std::output_iterator_tag;
  using value_type = void;
  using reference = void;
  using pointer = void;
  using difference_type = void;

  explicit LineWrapper(unsigned line_len = 80, ostream &os = std::cout)
      : max_len{line_len}, stream{os} {}

  LineWrapper &operator++() { return *this; }
  LineWrapper operator++(int) { return *this; }
  LineWrapper &operator*() { return *this; }
  template <typename T>
  LineWrapper &operator=(T const &val)
  {
    ostringstream oss;
    oss << val;
    auto const str{oss.str()};
    if (current_len != 0) {
      if (str.length() + current_len > max_len) {
        stream << '\n';
        current_len = 0;
      } else {
        ++current_len;
        stream << ' ';
      }
    }
    current_len += str.length();
    stream << str;
    return *this;
  }

private:
  unsigned const max_len;
  ostream &stream;
  unsigned current_len{};
};

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
