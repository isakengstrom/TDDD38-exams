#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

void compress(vector<pair<int, string>> & log)
{
    auto it {
        unique(log.begin(), log.end(),
               [](auto const & a, auto const & b)
               {
                   return a.second == b.second;
               })
            };
    if (it != log.end())
        log.erase(it, log.end());
}

auto diff(vector<pair<int, string>> const & log1,
          vector<pair<int, string>> const & log2)
{
    return mismatch(log1.begin(), log1.end(), log2.begin());
}

vector<pair<int, string>> merge(vector<pair<int, string>> const & log1,
                                vector<pair<int, string>> const & log2)
{
    vector<pair<int, string>> result { };
    merge(log1.begin(), log1.end(), log2.begin(), log2.end(),
          back_inserter(result), [](auto a, auto b)
          {
              return a.first < b.first;
          });
    compress(result);
    return result;
}

void print(pair<int, string> const & line)
{
    cout << '[' << setw(5) << setfill('0')
         << line.first << "]: " << line.second << std::endl;
}

int main()
{
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

