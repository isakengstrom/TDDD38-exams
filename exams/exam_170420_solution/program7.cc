#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int main()
{
    // 1
    vector<string> words { istream_iterator<string>{cin},
                           istream_iterator<string>{} };
    // 2
    map<string, int> frequencies;
    for_each(begin(words), end(words), 
             [&frequencies](string s){ frequencies[s]++; });
    // 3
    vector<pair<string, int>> wl {make_move_iterator(begin(frequencies)),
                                  make_move_iterator(end(frequencies))};
    sort(begin(wl), end(wl),
         [](auto p1, auto p2){return p1.second > p2.second;});
    // 4
    vector<string> replace (10);
    transform(begin(wl), next(begin(wl), 10), begin(replace),
            [](auto p){return p.first;});
    // 5
    transform(begin(words), end(words), begin(words),
             [&replace](string s){
             auto it = find(begin(replace), end(replace), s);
             if (it != end(replace) )
             {
                return "$" + to_string(distance(begin(replace), it));
             }
             return s;
             });
    // 6
    transform(begin(replace), end(replace), ostream_iterator<string>{cout, ";"},
              [index=0](string s) mutable { 
                ostringstream oss;
                oss << '$' << index++ << '=' << s;
                return oss.str();
                });
    cout << "\n";
    // 7
    copy(begin(words), end(words), ostream_iterator<string>{cout, " "});
}
