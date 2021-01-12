#include <iostream>
#include <string>
using namespace std;

// Define Celestial_Body classes here
class Celestial_Body
{
public:
    virtual ~Celestial_Body() = 0;
    std::string get_name() const
    {
        return name;
    }
    int get_size() const
    {
        return size;
    }
protected:
    Celestial_Body(std::string const & name, double size)
        : name{name}, size{size}
    {}
    Celestial_Body(Celestial_Body const &) = delete;
    Celestial_Body & operator=(Celestial_Body const &) = delete;
private:
    const std::string name;
    const double size;
};
//A pure virtual function is needed to actually get an abstract base class.
//Didn't require this at time of grading
Celestial_Body::~Celestial_Body() = default;

class Star final : public Celestial_Body
{
public:
    Star(string const & name, double size, string const & galaxy)
        : Celestial_Body{name, size}, galaxy{galaxy} 
    {}
    string get_galaxy() const
    {
        return galaxy;
    }
private:
    string const galaxy;
};

class Planet : public Celestial_Body
{
public:
    Planet(string const & name, double size, double orbit_time, Celestial_Body* orbits, bool populated = false)
        : Celestial_Body{name, size},
          orbit_time{orbit_time}, orbits{*orbits}, pop_status{populated}
    {}
    Celestial_Body * get_celestial_body() const
    {
        return &orbits;
    }
    double get_orbit_time() const
    {
        return orbit_time;
    }
    bool is_populated() const
    {
        return pop_status;
    }
    void populated(bool p)
    {
        pop_status = p;
    }
private:
    double orbit_time;
    Celestial_Body & orbits;
    bool pop_status;
};

class Moon final: public Planet
{
public:
    using Planet::Planet;
};

void print(const Celestial_Body& cb)
{
   // Depending on kind of celestial body, print its correspending data. Output
   // shall be as follows:
   // Helios: star, radius 696342.0 km, belongs to galaxy Milky Way
   // Earth: planet, radius 6371.0 km, belongs to star Helios, orbit time 365.2 days, populated
   // Moon: moon, radius 1737.1 km, belongs to planet Earth, orbit time 27.3 days, not populated
    auto sp = dynamic_cast<Star const*>(&cb);
    auto pp = dynamic_cast<Planet const *>(&cb);
    cout << cb.get_name() << ": ";
    if (sp)
        cout << "star";
    else if (pp)
        cout << "planet";
    else
        cout << "moon";
    cout << ", radius " << cb.get_size() << " km, belongs to ";
    if (sp)
        cout << "galaxy " << sp->get_galaxy();
    else
    {
        if (pp)
            cout << "star ";
        else
           cout << "planet ";
       cout << pp->get_celestial_body()->get_name() << ", orbit time " 
            << pp->get_orbit_time() << " days, " 
            << (pp->is_populated()?""s:"not "s) << "populated";
    }
    cout << endl;
}

int main()
{
   // Declare statically one object of each of type Star, Planet, and Moon. Use
   // the following data to initialize the objects (use defaults when suitable):
   // Star: name Helios, radius 696342.0, belongs to galaxy Milky Way
   // Planet: name Earth, radius 6371.0, belongs to star Helios, orbit time 365.2 days, populated
   // Moon: name Moon, radius 1737.1, belongs to planet Earth, orbit time 27.3 days, not populated
    Star h {"Helios", 696342, "Milky Way"};
    Planet e{"Earth", 6371, 365.2, &h, true};
    Moon m{"Moon", 1737.1, 27.3, &e};
   // Call print() for each object above.
    print(h);
    print(e);
    print(m);
   return 0;
}

