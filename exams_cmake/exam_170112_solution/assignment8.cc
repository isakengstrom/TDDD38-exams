#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    cerr << "Must be called with files containing start and end time\n";
    return 1;
  }
  ifstream start{argv[1]}, endstream{argv[2]};
  if (!start || !endstream)
  {
    cerr << "Couldn't open one of the files\n";
    return 2;
  }
  vector<string> intervals;
  transform(istream_iterator<int>{start}, istream_iterator<int>{},
            istream_iterator<int>{endstream}, back_inserter(intervals),
            [](int s, int e) {
              if (e < s)
              {
                e += 2400;
              }
              auto minutes = [](int t){return 60 * (t / 100) + t % 100;};
              int et{minutes(e)};
              int st{minutes(s)};
              int tot{et - st};
              int res{100 * (tot / 60) + tot % 60};
              stringstream ss;
              ss << setfill('0') << setw(4) << right << res;
              return ss.str();
            });
  auto minmax = minmax_element(begin(intervals), end(intervals));
  cout << "Largest element : " << *minmax.second
       << "\nSmallest element: " << *minmax.first << "\nAll elements\n";
  copy(begin(intervals), end(intervals),
       ostream_iterator<string>{cout, "\n"});
}
