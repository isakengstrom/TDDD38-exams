#include <vector>
#include <string>
#include <memory>
#include <iostream>
using namespace std;

class Slab
{
public:
    virtual ~Slab() noexcept = default;

    virtual Slab* clone() const = 0;
    string get_color() const
    {
        return color;
    }
    double get_weight() const
    {
        return weight;
    }
    string get_size() const
    {
        return size;
    }
protected:
    Slab(Slab const &) = default;
    Slab(string color, double weight, string size)
        : color{move(color)}, weight{weight}, size{move(size)} {}
private:
    string color;
    double weight;
    string size;
};

class Concrete final : public Slab
{
    public:
        Concrete(string color, double weight, string size, bool tumbled = false)
            : Slab{move(color), weight, move(size)}, tumbled_{tumbled} {}
        bool tumbled() const
        {
            return tumbled_;
        }
        Concrete * clone() const override
        {
            return new Concrete{*this};
        }
    private:
        bool tumbled_;
};

class Rock final : public Slab
{
public:
    Rock(double weight, string size, string type)
        : Slab{"Nature", weight, move(size)}, type{move(type)}
    {}
    string get_type() const
    {
        return type;
    }
    Rock * clone() const override
    {
        return new Rock{*this};
    }
private:
    string type;
};

class Brick final : public Slab
{
public:
    Brick(string color, double weight, string size)
        : Slab{move(color), weight, move(size)}
    {}
    Brick * clone() const override
    {
        return new Brick{*this};
    }
};

void test(Slab const & s)
{
    // Create a copy of the object that s refers to
    //
    // Print the information about the copy. With objects constructed according to the
    // comments in main, the printout should be:
    // Concrete: Gray, 25x12x4, 2.8kg
    // Rock: Granite, Nature, 12x15x10, 10.5kg
    // Brick: Red, 25x10x10, 3.2kg
    // Concrete: Graphite, 20x20x6, 3.9kg, tumbled
    //
    // Destroy the copy
    Slab const * p = s.clone();
    if ( dynamic_cast<Concrete const*>(p) )
    {
        cout << "Concrete: ";
    }
    else if (auto r = dynamic_cast<Rock const*>(p) )
    {
        cout << "Rock " << r->get_type() << ": ";
    }
    else
    {
        cout << "Brick: ";
    }
    cout << p->get_color() << ", " << p->get_size() << ", " << p->get_weight() << "kg";
    if ( auto c = dynamic_cast<Concrete const *>(p); c && c->tumbled())
    {
        cout << ", tumbled";
    }
    cout << endl;
    delete p;
}

int main()
{
    vector<unique_ptr<Slab>> slabs;
    slabs.emplace_back(make_unique<Concrete>("Gray", 2.8, "25x12x4"));
    slabs.emplace_back(make_unique<Rock>(10.5, "12x15x10", "Granite"));
    slabs.emplace_back(make_unique<Brick>("Red", 3.2, "25x25x10"));
    slabs.emplace_back(make_unique<Concrete>("Graphite", 3.9, "20x20x6", true));
    for ( auto && s: slabs )
    {
        test(*s);
    }
    // Create the following objects dynamically and store in some kind of container:
    // Type      Color    Size      Weight   type/tumbled
    // --------------------------------------------------
    // Concrete  Gray     25x12x4   2.8
    // Rock               12x15x10  10.5     Granite
    // Brick     Red      25x10x10  3.2
    // Concrete  Graphite 20x20x6   3.9      true

    // pass each object to test.

   return 0;
}
