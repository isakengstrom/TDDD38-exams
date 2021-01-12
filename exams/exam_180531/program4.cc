#include <vector>

using namespace std;


void apply_events(Context & c, vector</*const events*/> const v)
{
    for (auto & event : v)
        event->apply(c);
}

int main()
{
    Context c { };
    Named_Context nc { "My Context" };
    // add different events to the vector
    // at least one of each type
    vector</*const events*/> v {};
    apply_events(c, v);
    apply_events(nc, v);
}
