#include <iostream>
#include <vector>

using namespace std;

/* if implemented correctly this program
   should give the following output:

Gus eat Vegetarian Pizza.
Gus eat Calzone.
Gus eat Ham Pizza roll.
Gus eat Vegetarian Pizza roll.
Gus eat Salad.
Sally does not want Vegetarian Pizza.
Sally does not want Calzone.
Sally does not want Ham Pizza roll.
Sally does not want Vegetarian Pizza roll.
Sally eat Salad.
Pete eat Vegetarian Pizza.
Pete eat Calzone.
Pete does not want Ham Pizza roll.
Pete does not want Vegetarian Pizza roll.
Pete does not want Salad.
Velma eat Vegetarian Pizza.
Velma does not want Calzone.
Velma does not want Ham Pizza roll.
Velma eat Vegetarian Pizza roll.
Velma eat Salad.
*/

int main()
{

    vector</*Guest*/> guests {
        // Guest {"Gus"},
        // Salad_Lover {"Sally"},
        // Pizza_Lover {"Pete"},
        // Vegetarian {"Velma"}
    };

    // the true and false parameters represents
    // wheter or not the pizza/pizza roll is vegetarian
    vector</*Food*/> foods {
        // Pizza {"Vegetarian Pizza", true},
        // Pizza {"Calzone", false},
        // Pizza_Roll {"Ham Pizza", false},
        // Pizza_Roll {"Vegetarian Pizza", true},
        // Salad {"Salad"}
    };
    
    for (auto guest : guests)
    {
        for (auto food : foods)
        {
            // guest.eat(food);
            // or
            // guest->eat(food);
        }
    }
}
