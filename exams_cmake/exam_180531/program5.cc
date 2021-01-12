#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

using Log = vector<pair<int, string>>;

// modifies log to remove consecutive duplicates
void compress(Log & log);

// finds the first pair of entries which differs in log1 and log2.
// Returns a pair of iterators to these entries (one iterator for each
// log file).
/* pair of iterators*/ diff(Log const & log1, Log const & log2);

// Merges log1 and log2 into a sorted and compressed log file.
Log merge(Log const & log1, Log const & log2);


// test program begins here

// used to simplify the given tests
void print(pair<int, string> const & line)
{
    cout << '[' << setw(5) << setfill('0')
         << line.first << "]: " << line.second << std::endl;
}

/*

  If correct the output should be:

- log1 compressed:
[00000]: Message
[00005]: Test
[00006]: Stuff
[00008]: Test
[00009]: Message
- log1 diff log2:
log1: [00005]: Test
log2: [00001]: Message
- merge log1 and log2:
[00000]: Message
[00005]: Test
[00005]: Other test
[00006]: Stuff
[00008]: Test
[00009]: Message
[00009]: Things

 */

int main()
{
    // Note that these log files are not sorted
    vector<pair<int, string>> log1
    {
        { 0, "Message" },
        { 1, "Message" },
        { 4, "Message" },
        { 5, "Test" },
        { 6, "Stuff" },
        { 7, "Stuff" },
        { 8, "Test" },
        { 9, "Message" },
    };

    vector<pair<int, string>> log2
    {
        { 0, "Message" },
        { 1, "Message" },
        { 4, "Message" },
        { 5, "Other test" },
        { 6, "Stuff" },
        { 7, "Stuff" },
        { 8, "Test" },
        { 9, "Things" },
    };

    compress(log1);
    cout << "- log1 compressed:\n";
    for (auto const & entry : log1)
        print(entry);
    cout << "- log1 diff log2:\n";
    auto p { diff(log1, log2) };
    cout << "log1: ";
    print(*p.first);
    cout << "log2: ";
    print(*p.second);
    auto merged_logs { merge(log1, log2) };
    cout << "- merge log1 and log2:\n";
    for (auto const & entry : merged_logs)
        print(entry);
}
