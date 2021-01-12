#include <memory>
#include <vector>
#include <iostream>
using namespace std;

const int ROOM_TEMP = 22;

class Sauna
{
public:

    virtual ~Sauna() = default;
    Sauna * clone() const
    {
        return get_clone();
    }
    friend ostream & operator<<(ostream & os, Sauna const & s)
    {
        os << s.str() << " [";
        if ( s.is_on() )
        {
            os << "ON] " << s.temperature() << " degrees";
        } 
        else
            os << "OFF]";
        return os;
    }
    double temperature() const { return temp; }
    void set_temperature(double d)
    {
        temp = d;
    }
    void turn_on()
    {
        on = true;
        set_temperature(default_temp);
    }
    void turn_off()
    {
        on = false;
        set_temperature(ROOM_TEMP);
    }
    bool is_on() const { return on; }
protected:
    Sauna(double def = ROOM_TEMP)
        : default_temp{def} {}
    Sauna(Sauna const &) = default;

private:
    virtual string str() const = 0;
    virtual Sauna * get_clone() const = 0;
    double temp{ROOM_TEMP};
    double default_temp;
    bool on {};
};

class Steam_Sauna : public Sauna
{
public:
    Steam_Sauna() : Sauna{36} {}
private:
    Steam_Sauna(Steam_Sauna const &) = default;
    string str() const override
    {
        return "Steam";
    }
    Steam_Sauna * get_clone() const
    {
        return new Steam_Sauna{*this};
    }
};

class Wood_Sauna : public Sauna
{
public:
    Wood_Sauna() = default;
    void add_wood()
    {
        set_temperature(temperature()+5);
    }
private:
    Wood_Sauna(Wood_Sauna const &) = default;
    string str() const override
    {
        return "Wood burning sauna";
    }
    Wood_Sauna * get_clone() const
    {
        return new Wood_Sauna{*this};
    }
};

class Electrical_Sauna : public Sauna
{
public:
    Electrical_Sauna() : Sauna{85} {}
private:
    Electrical_Sauna(Electrical_Sauna const &) = default;
    string str() const override
    {
        return "Electrical sauna";
    }
    Electrical_Sauna * get_clone() const
    {
        return new Electrical_Sauna{*this};
    }
};


void do_stuff(unique_ptr<Sauna> s)
{
    cout << *s << endl;
    cout << "Turning on" << endl;
    s->turn_on();

    if ( auto ws = dynamic_cast<Wood_Sauna*>(s.get()) )
    {
        for ( int i {}; i < 12; ++i )
            ws->add_wood();
    }
    cout << *s << endl;
}


int main()
{
    vector<shared_ptr<Sauna>> saunas { make_shared<Steam_Sauna>(),                                    make_shared<Wood_Sauna>(), make_shared<Electrical_Sauna>() };
    for ( auto s : saunas )
    {
        do_stuff(unique_ptr<Sauna>{s->clone()});
    }
}
