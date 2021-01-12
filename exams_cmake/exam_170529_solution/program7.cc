#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cctype>
using namespace std;

int main()
{
    // 1
    vector<string> words { istream_iterator<string>{cin},
                           istream_iterator<string>{}};
    // 2
    cout << words.size() << " words read.\n";
    // 3
    for_each(begin(words), end(words),
            [](string & s)
            {
                transform(begin(s), end(s), begin(s), ::tolower);
            });
    // 4
    sort(begin(words), end(words));
    // 5
    words.erase(unique(begin(words), end(words)), end(words));
    // 6
    cout << words.size() << " unique words found.\n\n";
    // 7
    cout << "The unique words in alphabetical order:\n";
    copy(begin(words), end(words), ostream_iterator<string>{cout, " "});
    // 8
    // Words are sorted alphabetically, stable_sort is enough
    stable_sort(begin(words), end(words),
                [](string const & l, string const & r)
                {
                  return l.length() < r.length();
                });

    // 9
    cout << "\n\nThe unique words ordered by length:\n";
    copy(begin(words), end(words), ostream_iterator<string>{cout, " "});
}
