#include <string>
using namespace std;

template <typename T>
struct Type_Info {
  static string name() { return "UNKNOWN"; }
};

// Add your code here

int main() {
  array<int, 10> a;                         // expected output:

  cout << Meta_Type{5} << endl;             // int with size 4
  cout << Meta_Type<string>{"hej"} << endl; // string with size 3
  cout << Meta_Type{a} << endl;             // UNKNOWN with size 40
}
