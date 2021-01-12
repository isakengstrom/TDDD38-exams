#include <vector>
#include <string>
#include <cassert>

using namespace std;

int entry_score(string list)
{
  // calculate the score of an entry
}

int calculate_score(vector<string> const& list)
{
  // calculate the score of a wishlist
  return 0;
}

int main()
{
  {
    vector<string> list { "Fortnite", "Playstation 4", "Dog" };
    assert(calculate_score(list) == -62);
  }
  {
    vector<string> list { "Charcoal", "C++ Primer", "World Peace" };
    assert(calculate_score(list) == 35);
  }
  {
    vector<string> list { "Fortnite", "C++ Primer" };
    assert(calculate_score(list) == 20);
  }
  {
    vector<string> list { "Playstation 4", "Charcoal", "C++ Primer" };
    assert(calculate_score(list) == -17);
  }
}
