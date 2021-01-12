#include <memory>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>
using namespace std;

class Fruit
{
public:
    virtual ~Fruit() = default;
    virtual std::string name() const = 0;
    int vitamin_c_content() const
    {
        // fixes the concentration problem with a protected (or even private) virtual function
        return concentration()*mass()/100.0;
    }
    int mass() const
    {
        return mass_;
    }
    virtual bool dehiscent() const = 0;
    Fruit(int mass)
        : mass_{mass}
    {}
protected:
    virtual double concentration() const = 0;
private:
    // ONLY mass has to be stored (only thing that differs between two
    // objects of the same fruit)
    // Should be stored here since ALL fruit has a mass
    int mass_;
};

class Apple : public Fruit
{
public:
    Apple(int mass) : Fruit{mass}
    {}
    std::string name() const override
    {
        return "Apple";
    }
    bool dehiscent() const override
    {
        return false;
    }
protected:
    double concentration() const override
    {
        return 4.6;
    }
};

class Pea : public Fruit
{
public:
    using Fruit::Fruit;
    bool dehiscent() const override
    {
        return true;
    }
    std::string name() const override
    {
        return "Pea";
    }
    double concentration() const override
    {
        return 40;
    }
};

class Berry: public Fruit
{
public:
    using Fruit::Fruit;
    // final forbids subclasses to override, good since
    // all berries are indehiscent
    bool dehiscent() const override final
    {
        return false;
    }
};

class Lemon: public Berry
{
public:
    using Berry::Berry;
    std::string name() const override
    {
        return "Lemon";
    }
    double concentration() const override
    {
        return 53;
    }
};
void print(Fruit const & f)
{
    // some type of RTTI required
    if ( dynamic_cast<Berry const *>(&f) )
        cout << "Berry";
    else
        cout << "Fruit";
    cout << ", " << f.name() << " with mass " << f.mass() << "g [";
    if ( !f.dehiscent() )
    {
        cout << "in";
    }
    cout << "dehiscent]\n";

}

int main()
{
    // create a vector containing the following fruits:
    //  Apple, mass: 150g
    //  Lemon, mass: 75g
    //  Pea, mass: 25g
    //
    std::vector<std::unique_ptr<Fruit>> fruit;
    fruit.emplace_back(new Apple{150});
    fruit.emplace_back(new Lemon{75});
    fruit.emplace_back(new Pea{25});
    // Iterate through the vector and pass each fruit to print above, should give the following output
    // Fruit, Apple with mass 150g [indehiscent]
    // Berry, Lemon with mass 75g [indehiscent]
    // Fruit, Pea with mass 25g [dehiscent]
    for ( auto && f: fruit )
        print(*f);
   int total_content {};
    // Calculate the total vitamin C content of all fruit
    // accumulate not required, but a nice touch
    total_content = std::accumulate(begin(fruit), end(fruit), 0,
            [](int s,auto const & p){return s + p->vitamin_c_content();});
    cout << "Total vitamin C content: " << total_content << endl;
}
