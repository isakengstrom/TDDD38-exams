#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;


// Must compile with c++17
// Example: g++ program4.cc -std=c++17
int main()
{
  {
    vector<string> list {"first", "second", "third", "fourth"};

    /*
      Should output:
      1. first
      2. second
      3. third
      4. fourth
    */
    ostringstream ss{};
    copy(begin(list), end(list), print_list_iterator{ss});
    cout << ss.str() << endl;
    
    /*
      Should output:
      5. first
      6. second
      7. third
      8. fourth
    */
    copy(begin(list), end(list), print_list_iterator{cout, enumerate{5}});
    cout << endl;
    
    /*
      Should output:
      10. first
      12. second
      14. third
      16. fourth
    */
    copy(begin(list), end(list), print_list_iterator{cout, enumerate{10, 2}});
    cout << endl;
  }

  {
    vector<int> list{1, 2, 3, 4};
    
    /*
      Should output:
      (a) 1
      (b) 2
      (c) 3
      (d) 4
    */
    {
      vector<string> points{"(a)", "(b)", "(c)", "(d)"};
      copy(begin(list), end(list), print_list_iterator{cout, description<vector<string>>{points}});
      cout << endl;
    }
    
    /*
      Should output:
      (a) 1
      (b) 2
      (a) 3
      (b) 4
    */
    {
      vector<string> points{"(a)", "(b)"};
      copy(begin(list), end(list), print_list_iterator{cout, description<vector<string>>{points}});
      cout << endl;
    }
  }
  
  print_list_iterator printer{cout, enumerate{}};

  /*
    Should output:
    1. 1
    1. second
    2. 3.4
    2. f
  */
  printer = 1;
  printer = "second";
  ++printer;
  printer = 3.4;
  printer = 'f';
  
}
