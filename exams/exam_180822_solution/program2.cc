#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

class Food
{

public:

    Food(string const& name) : name{name} {}
    virtual ~Food() = default;

    virtual bool is_vegetarian() const = 0;
    string get_name() const { return name; }
    
protected:

    string const name;
    
};

class Pizza : public Food
{

public:

    Pizza(string const& name, bool vegetarian = false)
        : Food(name), vegetarian{vegetarian}
    {
    }

    bool is_vegetarian() const override
    {
        return vegetarian;
    }

private:

    bool const vegetarian;
};

class Pizza_Roll : public Pizza
{
public:

    Pizza_Roll(string const& name, bool vegetarian = false)
        : Pizza(name + " roll", vegetarian)
    {
    }
    
};

class Salad : public Food
{
public:

    using Food::Food;

    bool is_vegetarian() const override
    {
        return true;
    }
    
};

class Guest
{

public:

    Guest(string name) : name{name} {}
    virtual ~Guest() = default;
    void eat(Food const& food) const
    {
        cout << name;
        if (prefer(food))
        {
            cout << " eat ";
        }
        else
        {
            cout << " does not want ";
        }
        cout << food.get_name() << "." << endl;
    }

    virtual bool prefer(Food const&) const
    {
        return true;
    }
    
    
protected:

    string const name;
    
};

class Salad_Lover : public Guest
{

public:

    using Guest::Guest;

    bool prefer(Food const& food) const override
    {
        return dynamic_cast<Salad const*>(&food);
    }
    
};

class Vegetarian : public Guest
{

public:

    using Guest::Guest;

    bool prefer(Food const& food) const override
    {
        return food.is_vegetarian();
    }
    
};

class Pizza_Lover : public Guest
{

public:

    using Guest::Guest;

    bool prefer(Food const& food) const override
    {
        return typeid(food) == typeid(Pizza);
    }
    
};

int main()
{

    vector<Guest const*> guests {
        new Guest {"Gus"},
        new Salad_Lover {"Sally"},
        new Pizza_Lover {"Pete"},
        new Vegetarian {"Velma"}
    };
    
    vector<Food const*> foods {
        new Pizza {"Vegetarian Pizza", true},
        new Pizza {"Calzone"},
        new Pizza_Roll {"Ham Pizza"},
        new Pizza_Roll {"Vegetarian Pizza", true},
        new Salad {"Salad"}
    };
    
    for (auto guest : guests)
    {
        for (auto food : foods)
        {
            guest->eat(*food);
        }
        delete guest;
    }
    
    for (auto food : foods)
    {
        delete food;
    }
    
}
