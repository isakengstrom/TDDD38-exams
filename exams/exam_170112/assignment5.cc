#include <vector>
#include <iostream>
using namespace std;

void select_game(vector<Game*> const & games)
{
    for ( Game const * g: games )
    {
        if ( g->choose() )
        {
            g->print(cout);
            cout << endl;
        }
    }
}

int main()
{
    /* Create the following objects dynamically and store them in a vector
     *
     * Board game "Monopoly" has 2-4 players with a board of size 51x51cm
     * Cooperative board game "Pandemic" has 2-5 players with a board size 41x57cm
     * Card game "Solitaire" has 1 player and is played with a normal deck
     * Card game "Bang!" has 3-7 players and is played with a special deck
     * Cooperative board game "Battle Star Galactica" has 4-7 players with a board size of 100x120cm and can have a traitor
     */

     // call select_game, below are two examples:
     //
     /* 1:
      * How many players?: 2
      * Do you have space for 51x51cm [y/n]: y
      * -> Board game "Monopoly" has 2-4 players with a board of size 51x51cm
      * How many players?: 1
      * How many players?: 2
      * How many players?: 4
      * -> Card game "Bang!" has 3-7 players and is played with a special deck
      * How many players?: 5
      * Do you have space for 100x120cm? [y/n]: y
      * Do you want a traitor? [y/n]: y
      * -> Cooperative board game "Battle Star Galactica" has 4-7 players with a board size of 100x120cm and can have a traitor

      * 2:
      * How many players?: 2
      * Do you have space for 51x51cm? [y/n]: n
      * How many players?: 3
      * Do you have space for 41x57cm? [y/n]: y
      * Do you want a traitor? [y/n]:
      * -> Cooperative board game "Pandemic" has 2-5 players with a board size 41x57cm
      * How many players?: 5
      * How many players?: 5
      * -> Card game "Bang!" has 3-7 players and is played with a special deck
      * How many players?: 2
      */

}
