#include <type_traits>
#include <cassert>
#include <string>

/* implement your classes here */

int main()
{
  // is_same_v is true if both types in the template-argument list are the same
  // and false otherwise.
  assert((std::is_same_v<
          common_type<int, int>::type,
          int>));
  
  assert((std::is_same_v<
          common_type<int const, int>::type,
          int const>));
  
  assert((std::is_same_v<
          common_type<int, double>::type,
          double>));
  
  assert((std::is_same_v<
          common_type<double, int>::type,
          double>));
  
  assert((std::is_same_v<
          common_type<std::string, char const*>::type,
          std::string>));

  assert((std::is_same_v<
          common_type<void, int>::type,
          void>));

  assert((std::is_same_v<
          common_type<double, void>::type,
          void>));

  assert((std::is_same_v<
          common_type<void, void>::type,
          void>));
}
