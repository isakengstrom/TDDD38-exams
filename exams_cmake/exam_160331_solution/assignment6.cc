#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
class Score_Variant
{
public:
    virtual int score(vector<int> const &) const = 0;
    virtual string name() const = 0;
    virtual ~Score_Variant() = default;
protected:
    Score_Variant() = default;
private:
    Score_Variant(Score_Variant const &) = delete;
    Score_Variant & operator=(Score_Variant const &) = delete;
};

class Counted_Dice: public Score_Variant
{
public:
    int score(vector<int> const & dice) const override
    {
        int found {};
        for ( auto die : dice )
        {
            if ( die == value )
                ++found;
        }
        return value*found;
        // or value * count(begin(dice), end(dice), value);
    }
    int get_number() const { return value; }
protected:
    Counted_Dice(int lookfor): value{lookfor}
    {}
private:
    int value;
};

class Ones : public Counted_Dice
{
public:
    Ones(): Counted_Dice{1} {}
    string name() const override { return "Ones"; }
};

class Twos : public Counted_Dice
{
public:
    Twos(): Counted_Dice{2} {}
    string name() const override { return "Twos"; }
};

class Pair : public Score_Variant
{
public:
    int score(vector<int> const & dice) const override
    {
        auto d = dice;
        sort(begin(d), end(d), greater<int>{});
        auto it = adjacent_find(begin(d), end(d));
        if ( it != end(d) )
        {
            return (*it)*2;
        }
        return 0;
    }
    string name() const override
    {
        return "Pair";
    }
};

int main()
{
    // should really use some smart pointer, but fine without...
    const vector<Score_Variant*> score_variants {new Ones, new Twos, new Pair};
    vector<int> dice {1,4,1,5,4};
    for ( auto && variant : score_variants )
    {
        auto points = variant->score(dice);
        if ( points != 0 )
        {
            cout << variant->name() << ": " << points;
            if ( auto ptr = dynamic_cast<Counted_Dice*>(variant) )
            {
                cout << " (" << points / ptr->get_number() << ")";
            }
            cout << endl;
        }
    }
    // deallocate pointers
    for ( auto & variant : score_variants )
    {
        delete variant;
    }
}
