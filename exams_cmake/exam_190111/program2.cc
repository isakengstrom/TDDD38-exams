#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
Correct output should be:
  
Wednesday Addams hits Kevin McCallister with a snowball!
Wednesday Addams hits Rudolf with a snowball!
Kevin McCallister hits Rudolf with a snowball!
Rudolf hits Santa with a snowball!
Cupid hits Santa with a snowball!
Santa hits Wednesday Addams with a snowball!  
 */
int main()
{
  vector<Participant> participants {
    // Naughty_Child{"Wednesday Addams"},
    // Child{"Kevin McCallister"},
    // Reindeer{"Rudolf", true},
    // Reindeer{"Cupid", false},
    // Santa{}
  };

  for (auto p1 : participants)
  {
    for (auto p2 : participants)
    {
      if (/* check that p1 != p2 */)
      {
        if (p1.defeats(p2))
        {
          cout << p1.get_name() << " hits " << p2.get_name() << " with a snowball!" << endl;
        }
      }
    }
  }
}
