#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// keeps track on a position (x,y)
using Point = std::pair<int, int>;

// given a Movable object and a vector of objects, return true if there is a collision between
// the given Movable and any other object in the vector
bool have_collisions(/* some Movable */, /*vector of objects */ ) {
}

// Given a vector of Objects called objects, for each movable object, save the old position and call move().
// If there is a collision at the new location, reset the location to the saved, otherwise print that the object has moved.
void update(/* vector of Objects */) {
}

int main() {
    // Create a vector called objects storing the following objects:
    // Type    Name        Location (x,y)
    // Cat    "the cat"    (0,2)
    // Human  "the human"  (2,0)
    // Wall   "east wall"  (4,2)
    // Wall   "outer wall" (2,5)
    // Door   "front door" (2,3)


    // update all objects ten times (a very short game loop)
  for (int i{0}; i < 10; ++i)
    update(objects);

  // Should give the following output:
  // the cat moved!
  // the human moved!
  // the cat moved!
  // the human moved!
  // the cat moved!
  // the human moved!
  // the human moved!
}
