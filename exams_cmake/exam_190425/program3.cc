#include <cassert>
#include <string>
#include <vector>

/* implement your classes here */

bool has_redundancy(vector</* Operation */> const& operations)
{
    for (int i{1}; i < operations.size(); ++i)
    {
        if (/* operations[i] is redundant after operations[i-1] */)
            return true;
    }
    return false;
}

void apply(vector</* Operation */> const& operations, vector<string>& text)
{
    for (auto&& op : operations)
    {
        for (auto&& str : text)
        {
            str = /* apply op to str */;
        }
    }
}

int main()
{
    vector<string> test {"TDDD38", "Advanced", "programming", "in", "C++" };
    
    {
        vector<string> current {test};
        vector</* Operation */> operations {
            Capitalize{}, Lowercase{}, Lowercase{}
        };

        // Should have redundancy since we have two Lowecase in a row
        assert(has_redundancy(operations));
        apply(operations, current);
        assert((current == vector<string>{"tddd38", "advanced", "programming", "in", "c++"}));
    }
    {
        vector<string> current {test};
        vector</* Operation */> operations {
            Capitalize{}, Capitalize{}
        };

        // Should have redundancy since we have two Capitalize in a row
        assert(has_redundancy(operations));
        apply(operations, current);
        assert((current == vector<string>{"Tddd38", "Advanced", "Programming", "In", "C++"}));
    }
    {
        vector<string> current {test};
        vector</* Operation */> operations {
            Lowercase{}, Replace{'t', 'T'}, Replace{'d', 'D'}
        };

        assert(!has_redundancy(operations));
        apply(operations, current);
        assert((current == vector<string>{"TDDD38", "aDvanceD", "programming", "in", "c++"}));
    }
    {
        vector<string> current {test};
        vector</* Operation */> operations {
            Lowercase{}, Replace{'t', 'T'}, Replace{'t', 'V'}
        };

        // Should have redundancy since we have two replacers in a row
        // that replace the same character
        assert(has_redundancy(operations));
        apply(operations, current);
        assert((current == vector<string>{"Tddd38", "advanced", "programming", "in", "c++"}));
    }
}
