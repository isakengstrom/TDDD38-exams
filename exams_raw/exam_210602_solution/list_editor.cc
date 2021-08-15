#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Value
{
public:

    virtual ~Value() = default;
    virtual void print(std::ostream& os) const = 0;
    virtual Value* clone() const = 0;
};

template <typename T>
class Data : public Value
{
public:

    Data(T const& value)
            : value { value }
    { }

    void print(std::ostream& os) const override
    {
        os << value;
    }

    Value* clone() const override
    {
        return new Data<T>{value};
    }

    // public since this class is meant to represent a value directly.
    T value;

};

class Text : public Data<std::string>
{
public:

    using Data::Data;

    void print(std::ostream& os) const override
    {
        os << '\"';
        Data::print(os);
        os << '\"';
    }

    Value* clone() const override
    {
        return new Text{value};
    }
};

class List : public Value
{

    using iterator = std::vector<Value*>::iterator;

public:

    template <typename... Args>
    List(Args&&... args)
            : list{std::forward<Args>(args)...}
    { }

    List(std::vector<Value*> const& values)
            : list{std::begin(values), std::end(values)}
    { }

    ~List()
    {
        for (Value* v : list)
        {
            delete v;
        }
    }

    void print(std::ostream& os) const override
    {
        os << "[ ";

        std::for_each(std::begin(list), std::end(list),
                      [&os](Value const* v)
                      {
                          v->print(os);
                          os << ' ';
                      });
        os << "]";
    }

    Value* clone() const override
    {
        std::vector<Value*> result(list.size());

        std::transform(std::begin(list), std::end(list), std::begin(result),
                       [](Value const* v) { return v->clone(); });

        return new List{result};
    }

    iterator begin()
    {
        return list.begin();
    }

    iterator end()
    {
        return list.end();
    }

    void remove(iterator left, iterator right)
    {
        list.erase(left, right);
    }

    template <typename It>
    void insert(It left, It right)
    {
        std::copy(left, right, std::back_inserter(list));
    }

private:

    std::vector<Value*> list { };
};


class Operation
{
public:
    virtual ~Operation() = default;
    virtual void apply(Value* value) = 0;

protected:

    static List* to_list(Value* value)
    {
        return dynamic_cast<List*>(value);
    }
};

class Duplicate : public Operation
{
public:

    void apply(Value* value) override
    {
        List* list { to_list(value) };
        if (!list) return;

        std::vector<Value*> result { list->begin(), list->end() };
        std::transform(std::begin(result), std::end(result), std::begin(result),
                       [](Value* v) { return v->clone(); });
        list->insert(std::begin(result), std::end(result));
    }
};

template <typename Predicate>
class Filter : public Operation
{
public:

    Filter(Predicate predicate)
            : predicate { predicate }
    { }

    void apply(Value* value) override
    {
        List* list { to_list(value) };
        if (!list) return;

        auto it = std::remove_if(list->begin(), list->end(),
                                 [this](Value* v)
                                 {
                                     if (!predicate(v))
                                     {
                                         delete v;
                                         return true;
                                     }
                                     return false;
                                 });

        list->remove(it, list->end());

    }

private:

    Predicate predicate;
};

class Replace_Text : public Operation
{
public:

    void apply(Value* value) override
    {
        List* list { to_list(value) };
        if (!list) return;

        for (Value* value : *list)
        {
            Text* text = dynamic_cast<Text*>(value);
            if (text)
            {
                auto it = table.find(text->value);
                if (it != std::end(table))
                {
                    text->value = it->second;
                }
            }
        }
    }

    void insert(std::string const& key, std::string const& value)
    {
        table[key] = value;
    }

private:

    std::unordered_map<std::string, std::string> table { };
};

//===========================
//======== Testcases ========
//===========================

bool pred0(Value const* value)
{
    return dynamic_cast<Text const*>(value);
}

bool pred1(Value const* value)
{
    Data<int> const* data = dynamic_cast<Data<int> const*>(value);
    return data == nullptr || data->value >= 0;
}

/* Expected output:

Testcase 1:
[ 0 "Hello" 1 "World!" ]
After filtering out only strings:
[ "Hello" "World!" ]
After replace text:
[ "Howdy" "World!" ]

Testcase 2:
[ 1 -5 2 "-3" ]
After duplication:
[ 1 -5 2 "-3" 1 -5 2 "-3" ]
After filtering out positive integers:
[ 1 2 "-3" 1 2 "-3" ]

Testcase 3:
[ "A" [ "B" "C" ] "D" ]
After duplication:
[ "A" [ "B" "C" ] "D" "A" [ "B" "C" ] "D" ]

*/

int main()
{
    {
        List list { new Data<int>{0}, new Text{"Hello"},
                    new Data<int>{1}, new Text{"World!"} };

        Filter op1 { pred0 };

        std::cout << "Testcase 1:" << std::endl;

        list.print(std::cout);
        std::cout << std::endl;

        std::cout << "After filtering out only strings:" << std::endl;

        op1.apply(&list);
        list.print(std::cout);
        std::cout << std::endl;

        Replace_Text op2 { };
        op2.insert("Hello", "Howdy");

        std::cout << "After replace text:" << std::endl;

        op2.apply(&list);
        list.print(std::cout);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    {
        List list { new Data<int>{1}, new Data<int>{-5},
                    new Data<int>{2}, new Text{"-3"} };

        Duplicate op1 { };

        std::cout << "Testcase 2:" << std::endl;

        list.print(std::cout);
        std::cout << std::endl;

        std::cout << "After duplication:" << std::endl;

        op1.apply(&list);
        list.print(std::cout);
        std::cout << std::endl;

        Filter op2 { pred1 };

        std::cout << "After filtering out positive integers:" << std::endl;

        op2.apply(&list);
        list.print(std::cout);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    {
        List list { new Text{"A"},
                    new List{ new Text{"B"}, new Text{"C"} },
                    new Text{"D"} };

        std::cout << "Testcase 3:" << std::endl;
        list.print(std::cout);
        std::cout << std::endl;

        Duplicate op1 { };

        std::cout << "After duplication:" << std::endl;

        op1.apply(&list);
        list.print(std::cout);
        std::cout << std::endl;
    }
}