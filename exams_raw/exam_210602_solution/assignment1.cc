template <typename T, typename... Ts>
struct Contains;

template <typename T, typename... Rest>
struct Contains<T, T, Rest...>
{
    static constexpr bool value = true;
};

template <typename T, typename First, typename... Rest>
struct Contains<T, First, Rest...>
{
    static constexpr bool value = Contains<T, Rest...>::value;
};

template <typename T>
struct Contains<T>
{
    static constexpr bool value = false;
};

template <typename... Ts>
struct Is_Set;

template <>
struct Is_Set<>
{
    static constexpr bool value = true;
};

template <typename T, typename... Ts>
struct Is_Set<T, Ts...>
{
    static constexpr bool value = (!Contains<T, Ts...>::value) && Is_Set<Ts...>::value;
};

int main()
{
    static_assert(Is_Set<int, float>::value);
    static_assert(!Is_Set<int, int, bool>::value);
    static_assert(!Is_Set<float, int, bool, float>::value);
}

// Explain what a fold-expression is. Are there any advantages to
// fold-expression compared to variadic recursion?

// Fold-expressions are expressions introduced in C++17 that operates
// on unexpanded variadic parameter packs. A fold-expression will
// apply a binary operator over the parameter pack, for example
// operator+ or operator,

// Example:

// (args + ... + 0)

// This is a lot faster during compile-time compared to variadic
// recursion. This is manly because variadic recursion leverages the
// template instantiation logic of the compiler to reduce the
// expressions. This means that with variadic recursion the compiler
// *must* instantiate many classes/functions to evaulate the
// recursion. Compare this to a language feature specifically designed
// to do this kind of work. This allows the compiler authors to be
// more specific in their optimizations, so chances are that besides
// the gained compile-time we might get better optimized code with
// fold-expressions.

// Another benefit with fold-expressions are that they are a lot
// clearer to read and understand. A drawback however is that it is
// not as powerful as variadic recursion.