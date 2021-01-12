#include <string>
#include <iostream>
#include <utility> // std::declval
#include <vector>
#include <list>
#include <sstream>
#include <cassert>

using namespace std;

/* create three different helper functions:
   1. one for string
   2. one for all types which has a push_back member
   3. every other type
   
   The third argument (int or long) is declared so that no
   ambigouities will arise while matching an overload.
   
   If there is a conflict (for example; std::vector<T> can match the
   second and third overload) the compiler will nortice that the third
   argument is '0' which is an int. The overload which takes an int
   (i.e. the second overload) will be choosen since this is a closer
   match.

   If there are no overloads that matches where the third argument is
   int, the '0' will be implicitly converted to long.

   In this manner it is possble to specify a priority order.
*/
void prompt_helper(istream& is, string& result, int)
{
    getline(is, result);
}

/* Using expression SFINAE to remove overload for T that have no
   push_back member (nor a value_type). As previously stated;
   the extra argument is there to tell the compiler to prefer
   this overload over the more general prompt_helper if at all
   possible (i.e. if T has push_back and value_type).
 */
template <typename T>
auto prompt_helper(istream& is, T& result, int)
    -> decltype(result.push_back(declval<typename T::value_type>()),
                declval<void>())
{
    typename T::value_type tmp;
    while (is >> tmp)
        result.push_back(tmp);
}

template <typename T>
void prompt_helper(istream& is, T& result, long)
{
    is >> result;
}

template <typename T>
T prompt(istream& is)
{
    T result;
    prompt_helper(is, result, 0);
    return result;
}

int main()
{
    {
        istringstream iss{"57"};
        auto val = prompt<int>(iss);
        assert(val == 57);
    }
    {
        istringstream iss{"3.141592"};
        auto val = prompt<double>(iss);
        assert(val == 3.141592);
    }
    {
        istringstream iss{"this is a test"};
        auto val = prompt<string>(iss);
        assert(val == "this is a test");
    }
    {
        vector<int> result{1, 2, 3, 4, 5};
        istringstream iss{"1 2 3 4 5"};
        auto val = prompt<vector<int>>(iss);
        assert(val == result);
    }
    {
        list<string> result{"this", "is", "a", "test"};
        istringstream iss{"this is a test"};
        auto val = prompt<list<string>>(iss);
        assert(val == result);
    }
}
