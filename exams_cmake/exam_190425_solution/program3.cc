#include <algorithm>
#include <cassert>
#include <cctype>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace std::literals;

class Operation
{
public:
    Operation() = default;
    Operation(Operation const&) = delete;
    virtual ~Operation() = default;    
    virtual string apply(string const& str) = 0;
    virtual bool redundant_after(Operation const& p) const = 0;
};

class Lowercase : public Operation
{
public:
    string apply(string const& str) override
    {
        string result{str};
        transform(begin(result), end(result), begin(result), ::tolower);
        return result;
    }
    
    bool redundant_after(Operation const& op) const
    {
        return typeid(op) == typeid(Lowercase);
    }
};

class Capitalize : public Lowercase
{
public:
    string apply(string const& str) override
    {
        string result {Lowercase::apply(str)};
        result.front() = toupper(result.front());
        return result;
    }

    bool redundant_after(Operation const& op) const
    {
        return typeid(op) == typeid(Capitalize);
    }
};

class Replace : public Operation
{
public:
    Replace(char target, char replacement)
        : target{target}, replacement{replacement}
    { }

    string apply(string const& str) override
    {
        string result{str};
        replace(begin(result), end(result), target, replacement);
        return result;
    }

    bool redundant_after(Operation const& op) const override
    {
        if (auto ptr = dynamic_cast<Replace const*>(&op); ptr)
        {
            if (ptr -> target == target)
                return true;
        }
        return false;
    }
    
private:
    char target;
    char replacement;
};

bool has_redundancy(vector<Operation*> const& operations)
{
    for (int i{1}; i < operations.size(); ++i)
    {
        if (operations[i]->redundant_after(*operations[i-1]))
            return true;
    }
    return false;
}

void apply(vector<Operation*> const& operations, vector<string>& text)
{
    for (auto&& op : operations)
    {
        for (auto&& str : text)
        {
            str = op->apply(str);
        }
    }
}

int main()
{
    vector<string> test {"TDDD38", "Advanced", "programming", "in", "C++" };
    
    { 
        vector<string> current {test};
        vector<Operation*> operations {
            new Capitalize{}, new Lowercase{}, new Lowercase{}
        };
        
        assert(has_redundancy(operations));
        apply(operations, current);
        assert((current == vector<string>{"tddd38", "advanced", "programming", "in", "c++"}));
        
        for (auto p : operations)
            delete p;
    }
    {
        vector<string> current {test};
        vector<Operation*> operations {
            new Capitalize{}, new Capitalize{}
        };
        
        assert(has_redundancy(operations));
        apply(operations, current);
        assert((current == vector<string>{"Tddd38", "Advanced", "Programming", "In", "C++"}));
        
        for (auto p : operations)
            delete p;
    }
    {
        vector<string> current {test};
        vector<Operation*> operations {
            new Lowercase{}, new Replace{'t', 'T'}, new Replace{'d', 'D'}
        };
        
        assert(!has_redundancy(operations));
        apply(operations, current);
        assert((current == vector<string>{"TDDD38", "aDvanceD", "programming", "in", "c++"}));
        
        for (auto p : operations)
            delete p;
    }
    {
        vector<string> current {test};
        vector<Operation*> operations {
            new Lowercase{}, new Replace{'t', 'T'}, new Replace{'t', 'V'}
        };
        
        assert(has_redundancy(operations));
        apply(operations, current);
        assert((current == vector<string>{"Tddd38", "advanced", "programming", "in", "c++"}));
        
        for (auto p : operations)
            delete p;
    }
}
