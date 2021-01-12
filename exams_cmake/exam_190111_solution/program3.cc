#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cassert>

using namespace std;

int entry_score(string list)
{
  if (list.empty())
    return 0;
  vector<int> result{};
  transform(begin(list), end(list), begin(list), ::tolower);
  adjacent_difference(begin(list), end(list), back_inserter(result));
  result.erase(begin(result));
  vector<double> weights(result.size());
  iota(begin(weights), end(weights), 1.0);
  transform(begin(weights), end(weights), begin(weights),
            [size = weights.size()](double a) { return a / size; });
  return inner_product(begin(result), end(result), begin(weights), 0.0);
}

int calculate_score(vector<string> const& list)
{
  vector<double> scores(list.size());
  transform(begin(list), end(list), begin(scores), entry_score);
  return accumulate(begin(scores), end(scores), 0);
}

int main()
{
  {
    vector<string> list { "Fortnite", "Playstation 4", "Dog" };
    assert(calculate_score(list) == -62);
  }
  cout << "Fortnite: " << entry_score("Fortnite") << endl;
  cout << "Playstation 4: " << entry_score("Playstation 4") << endl;
  cout << "Dog: " << entry_score("Dog") << endl;
  cout << "Charcoal: " << entry_score("Charcoal") << endl;
  cout << "C++ Primer: " << entry_score("C++ Primer") << endl;
  cout << "World Peace: " << entry_score("World Peace") << endl;
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
