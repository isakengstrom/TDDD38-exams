#include <array>
#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>

using namespace std;

template <typename T>
struct Type_Info
{
  static string name() { return "UNKNOWN"; }
};

template <>
struct Type_Info<int>
{
  static string name() { return "int"; }
};

template <>
struct Type_Info<string>
{
  static string name() { return "string"; }
};

// Using expression SFINAE to remove overload for types not
// having a size member function. The extra argument is to
// prefer this overload for types that have a size member
// since both can be instantiated.
template <typename T>
auto size_helper(T const &val, int) -> decltype(val.size()) {
  return val.size() * sizeof(typename T::value_type);
}

template <typename T>
size_t size_helper(T const &val, long) {
  return sizeof(val);
}

template <typename T>
struct Meta_Type
{
  static string name() { return Type_Info<T>::name(); }
  size_t size() const { return size_helper(value, 0); }
  Meta_Type(T const &t) : value{t} {}
  T const &value;
};

template <typename T>
ostream &operator<<(ostream &os, Meta_Type<T> const &type)
{
  return os << type.name() << " with size " << type.size();
}

int main() {
  array<int, 10> a;                         // expected output:

  cout << Meta_Type{5} << endl;             // int with size 4
  cout << Meta_Type<string>{"hej"} << endl; // string with size 3
  cout << Meta_Type{a} << endl;             // UNKNOWN with size 40
}
