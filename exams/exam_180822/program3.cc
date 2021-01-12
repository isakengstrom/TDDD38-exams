#include <functional> // for std::plus and std::minus
#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <string>

using namespace std;

/* This program MUST be compiled with C++17 since it relies on
   template argument deduction.

   If everything is implemented correctly, this program should
   give the following output:
   
   vector<double>: 1, 2.1, 2.14, 2.1405, 3.1415, 
   vector<int>: 5, 2, 1, 1, 0, 
   list<string>: du, du hast, du hast mich, 
   deque<pair<int,int>>: (1, 1), (6, 3), (8, 8), (10, 9), (10, 10), 
   deque<int>:

*/

int main()
{
    {
        vector<double> vals { 1.0, 1.1, 0.04, 0.0005, 1.001 };
        cout << "vector<double>: ";
        for (auto res : fold(vals))
            cout << res << ", ";
        cout << endl;
    }

    {
        vector<int> vals { 5, 3, 1, 0, 1 };
        cout << "vector<int>: ";
        for (auto res : fold(vals, 10, minus<int>{}))
            cout << res << ", ";
        cout << endl;
    }

    {
        list<string> vals { "du", " hast", " mich" };
        cout << "list<string>: ";
        for (auto res : fold(vals))
            cout << res << ", ";
        cout << endl;
    }

    {
        deque<pair<int, int>> vals { {1, 1}, {5, 2}, {2, 5}, {2, 1}, {0, 1} };
        cout << "deque<pair<int,int>>: ";
        for (auto res : fold(vals, pair<int, int>{0, 0},
                    [](auto a, auto b)
                    {
                        return pair<int, int>{a.first + b.first, a.second + b.second};
                    }
                 ))
            cout << "(" << res.first << ", " << res.second << "), ";
        cout << endl;
    }

    {
        deque<int> vals {};
        cout << "deque<int>: ";
        for (auto res : fold(vals))
            cout << res << ", ";
        cout << endl;
    }
}
