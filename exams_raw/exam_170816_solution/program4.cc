#include <iostream>
#include <iomanip>
#include <vector>
struct Any 
{
    template <typename T>
    bool prefix(T const & val)
    {
        return static_cast<bool>(val);
    }

    bool combine(bool a, bool b)
    {
        return a || b;
    }
    bool done(bool v)
    {
        return v;
    }
    static constexpr const bool done_result {true};

    static constexpr const bool start { false };
};

struct None 
{
    template <typename T>
    bool prefix(T const & val)
    {
        return !static_cast<bool>(val);
    }

    bool combine(bool a, bool b)
    {
        return a && b;
    }
    bool done(bool v)
    {
        return v;
    }
    static constexpr const bool done_result {false};

    static constexpr const bool start { false };
};

struct All 
{
    template <typename T>
    bool prefix(T const & val)
    {
        return static_cast<bool>(val);
    }

    bool combine(bool a, bool b)
    {
        return a && b;
    }
    bool done(bool v)
    {
        return !v;
    }
    static constexpr const bool done_result {false};

    static constexpr const bool start { true };
};

struct AtLeast
{
    AtLeast(int N): count{N} {}
    template <typename T>
        bool prefix(T const & t)
        {
            auto val = static_cast<bool>(t);
            if ( val )
                --count;
            return val;

        }
    bool combine(bool, bool)
    {
        return false;
    }
    bool done(bool)
    {
        return 0==count;
    }
    int count;
    static constexpr const bool done_result { true }; 
    static constexpr const bool start { false };

};

template <typename It, typename CombType = All>
bool logic_combine(It start, It end, CombType c = {})
{
    auto res { CombType::start };
    for ( It cur { start }; cur != end; ++cur )
    {
        res = c.combine(res, c.prefix(*cur));
        if (c.done(res))
            return CombType::done_result;
    }
    return res;
}

// Main function. The output should be
// true
// false
// true
// false
int main()
{
    std::vector<int> vals {0,0,0,1};
    auto b { begin(vals) };
    auto e { end(vals) };
    using namespace std;
    cout << boolalpha
         << logic_combine(b,e, AtLeast{1}) << '\n'
         << logic_combine(b,e, AtLeast{8}) << '\n'
         << logic_combine(b,e, Any{}) << '\n'
         << logic_combine(b,e) << '\n';
}
