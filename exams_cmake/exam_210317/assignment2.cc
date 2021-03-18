#include <cassert>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

int test_0 { 0 };
void fun_0(int x)
{
    test_0 += x;
}

int main()
{
    {

        // Notice that the key of the std::map doesn't matter, we are
        // only interested in the value for each entry in the map.
        
        std::vector<std::map<std::string, std::set<int>>> structure {

            std::map<std::string, std::set<int>>{
                { "a", { 1, 2, 3 } },
                { "b", { 6, 5, 4 } },
                { "c", { 8, 9, 7, 10 } }
            },

            std::map<std::string, std::set<int>>{
                { "b", { 1, 5 } },
                { "d", { 9, 3 } },
                { "e", { 7 } }
            },
            
        };

        iterate_leaves(structure, fun_0);
        assert(test_0 == ( (1 + 2 + 3) + (6 + 5 + 4) + (8 + 9 + 7 + 10) ) + ( (1 + 5) + (9 + 3) + (7) ));
        
    }


    {
        std::set<std::vector<double>> structure {

            { 1.2, 3.45, 6.0 },
            { 7.11, 9.8, 10.12 },
            { 13.0 }
            
        };

        // iterate_leaves should work just like std::for_each in this
        // case since the passed in callable object (the lambda)
        // operates on std::vector<double>
        std::vector<double> total { };
        iterate_leaves(structure, [&total](std::vector<double> const& v)
                                  {
                                      for (double d : v)
                                      {
                                          total.push_back(d);
                                      }
                                  });

        assert( (total == std::vector<double>{ 1.2, 3.45, 6.0, 7.11, 9.8, 10.12, 13.0 }) );
    }
}
