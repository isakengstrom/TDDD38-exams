/*
 * program9.cc
 */
#include <string>
using namespace std;

class Wrapper
{
public:
   Wrapper(int value = 0) : value_{ value } {}

private:
   int value_;
};

int main()
{
   Wrapper wi{ 1 };                  // to be Wrapper<int>

   Wrapper* wip = new Wrapper{ 2 };  // to be Wrapper<int>*

//   Wrapper<double> wd{ 2.3 };

   delete wip;

//   Wrapper<char> wch;

   return 0;
}
