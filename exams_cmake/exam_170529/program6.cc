#include <iostream>
using namespace std;


void print(Fruit const & f)
{
    // Print Berry if f is a berry or Fruit otherwise

    cout << f.name() << " with mass " << f.mass() << "g [";
    if ( !f.dehiscant() )
    {
        cout << "in";
    }
    cout << "dehiscant]\n";

}

int main()
{
    // create a vector containing the following fruits:
    //  Apple, mass: 150g
    //  Lemon, mass: 75g
    //  Pea, mass: 25g
    //

    // Iterate through the vector and pass each fruit to print above, should give the following output
    // Fruit, Apple with mass 150g [indehiscant]
    // Berry, Lemon with mass 75g [indehiscant]
    // Fruit, Pea with mass 25g [dehiscant]

   int total_content {};
    // Calculate the total vitamin C content of all fruit

    cout << "Total vitamin C content: " << total_content << endl;
}
