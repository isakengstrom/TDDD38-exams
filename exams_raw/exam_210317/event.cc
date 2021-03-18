// Suggestions and hints:

// - Read the 'main' function to understand how the code is used.

// - Don't worry too much about rewriting everything. Find a few
//   places where you can demonstrate your knowledge and only change
//   those places.

// - The wishlists are just hints/suggestions. You don't have to
//   follow them if you don't want to.

// - It is more important to understand how the code is used rather
//   than what it does.

// - To help you understand the code it might be helpful to make small
//   changes in the code and then see what effect it has on the
//   output.

// - It is ok if the behaviour of the code changes, as long as it
//   stays approximately the same. Use your own judgement.

// - If you feel like you have fulfilled the requirements for the exam
//   it is not necessary to modify every piece of code that might be
//   broken due to your changes. You can safely remove any function
//   that is not strictly necessary for your solution.

// - There are a lot of comments in this file, read them.

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cassert>

struct Action;

enum Action_Type
{
    CALLBACK,
    LOG,
    MULTI
};

// This class represents all the possible actions that can be taken
// whenever an event is triggered, these are:

// - CALLBACK : calls an arbitrary function 'callback' with signature
//              'void(Action*)' whenever the action is triggered.

// - LOG : prints a specified message ('message') to the terminal.

// - MULTI : an action consisting of an arbitrary number of other
//           actions, all of which are triggered when this action is
//           triggered.

// These actions are also printable, mainly so that the current state
// of the event system can be printed in a somewhat readable manner.

// Wishlist:

// - It would be a good idea to represent the 'type' in some other way.

// - It should be easy to add other types of actions.

// - Would be nice if 'log' could log other things than a string.

// - In the current implementation, 'callback' can only call actual
// - functions. It would be strongly beneficial if callback could call
// - all callable objects: functions, lambdas and function objects.

// - Can we store only the relevant data member for the corresponding
//   type somehow?

// Callback is a data type: namely a pointer to a function that
// returns void and takes an Action* as a parameter.
using Callback = void (*)(Action*);
struct Action
{
    Action_Type type { };
    
    // CALLBACK
    Callback callback { };

    // LOG
    std::string message { };

    // MULTI
    std::vector<Action*> subactions { };
};

// This function is meant to print what type of action 'action' is,
// but it isn't supposed to tell us exactly what the action does.

// Whishlist:

// - Would be nice if we didn't have to check the type of the action.

void print(Action* action, std::ostream& os)
{
    if (action->type == CALLBACK)
    {
        os << "callback";
    }
    else if (action->type == LOG)
    {
        os << "log";
    }
    else if (action->type == MULTI)
    {
        os << "[ ";

        for (Action* subaction : action->subactions)
        {   
            print(subaction, os);
            os << ' ';
        }
        
        os << ']';
    }
}

// This function is the main feature of the Action struct.  Whenever
// the System triggers an Event, that event will then call this
// function on its Action.

// Whishlist:

// - Would be nice if we didn't have to check the type of the action.

// - Can we iterate through 'subactionss' in any other way? With some
//   algorithm maybe?

void trigger(Action* action)
{
    if (action->type == CALLBACK)
    {
        // Call the callback function
        action->callback(action);
    }
    else if (action->type == LOG)
    {
        std::clog << "Triggered: " << action->message << std::endl;
    }
    else if (action->type == MULTI)
    {
        for (Action* subaction : action->subactions)
        {
            trigger(subaction);
        }
    }
}

// Constructors for the different Action types

Action* create_callback(Callback callback)
{
    Action* action { new Action { CALLBACK } };
    action->callback = callback;
    return action;
}

Action* create_log(std::string const& message)
{
    Action* action { new Action { LOG } };
    action->message = message;
    return action;
}


// Wishlist:

// - Would be nice if we could pass an arbitrary number of Action* to
//   the function directly rather than having to wrap it in a vector
//   first.

Action* create_multi(std::vector<Action*> const& actions)
{
    Action* action { new Action { MULTI } };
    action->subactions = actions;
    return action;
}

// The different types of events that can occur.
enum Event_Type
{
    USER,
    IO,
    EXIT
};

// This struct represents an event that is registered in the system.
// Event is not meant to be used by the end-user, instead this is an
// internal class that is used inside the logic of the System.

// Wishlist:

// - Would be nice if this struct was hidden from the user, or at the
//   very least not usable by the user.

struct Event
{
    unsigned id { };
    Action* action { };
};

// Will print the id and action of the event.
void print(Event const& event, std::ostream& os)
{
    os << "Event #" << event.id << ": ";
    print(event.action, os);
}

// Simply triggers the underlying action.
void trigger(Event& event)
{
    trigger(event.action);
}

// System is the main functionality of the event-system. It contains a
// lookup table where we associate a list of events with a specific
// event type. We call each row in this table 'Entry', which contains
// the event type and all events that are currently registered to that
// event type. Note that the content of the list is dynamic, meaning
// events can be added or removed whenever.

// Each event must have a unique identifier. The easiest way to make
// that happen is to just have a counter ('free_id') that increases
// everytime a new event is registered to the system. This will of
// course create gaps when events are removed, but that is OK for this
// particular system.

// There are several functions associated with this struct (look under
// the struct).

// Wishlist:

// - It seems awfully inefficient to use std::vector here. If only
//   there was a container that allowed us to lookup values based on
//   Event_Type.

// - Maybe it is a bad idea to allow the user full access to the
// - 'free_id' and 'events' members.

// Wishlist:

// - This struct is riddled with memory leaks. As it stands right now,
//   it is up to the user to manage the memory of actions. This is
//   generally speaking bad design, so if we somehow could make sure
//   that memory is cleaned up within the system itself that would be
//   good.
using Entry = std::pair<Event_Type, std::vector<Event>>;
struct System
{
    unsigned free_id { 0 };
    std::vector<Entry> events { };
};

// Primarily used so that we can examine the current state of the
// system. Will print each event in the entire system. The order they
// are printed doesn't really matter.
void print(System const& system, std::ostream& os)
{
    for (Entry const& entry : system.events)
    {
        for (Event const& event : entry.second)
        {
            print(event, os);
            os << std::endl;
        }
    }
}

// Creates a new entry in the system. Will create a new event which
// contains 'action' that is assigned a unique id. This unique id is
// then returned to the user. This works kind of like a ticket, so
// whenever the user wants to do something with this event (in this
// case we can only remove events, but for scalability it is good to
// have), the user can then simply pass this ticket (id) to the system
// and that will uniquely identify the event.

unsigned register_event(System& system, Event_Type type, Action* action)
{
    unsigned id { system.free_id++ };

    // Find the entry for 'type'
    std::size_t i { 0 };
    for (; i < system.events.size(); ++i)
    {
        if (system.events[i].first == type)
        {
            break;
        }
    }

    // If no entry was found add a new one 
    if (i == system.events.size())
    {
        system.events.push_back( Entry{ type, {} } );
    }

    // Insert the event
    Event event { id, action };
    system.events[i].second.push_back(event);

    return id;
}

// This function will go through each event in the entire system and
// remove those events for which the passed in function 'predicate'
// returns true.

// The way removal is done is very simple: it will swap the found
// event with the one at the back of the list and then remove the last
// one (which is now the event we want to remove).

// Wishlist:

// - Would be nice if Predicate could be any callable object, not
//   just functions.

// - Is there a better way to remove all events for each event type
//   that fullfills the predicate? Maybe some algorithm?

using Predicate = bool (*)(Event const&);
void remove_event(System& system, Predicate predicate)
{
    for (Entry& entry : system.events)
    {
        for (std::size_t i { 0 }; i < entry.second.size(); ++i)
        {
            if (predicate(entry.second[i]))
            {
                std::swap(entry.second[i], entry.second.back());
                entry.second.pop_back();
            }
        }
    }
}

// This function removes the event with the specified 'id'. Will
// remove any duplicates if theu happen to exist (but they really
// shouldn't be able to exist if all variables are properly hidden
// from the user).

// Wishlist:

// - This is very similar to the other 'remove_event' overload. Can it
//   be reused somehow to minimize code duplication?

void remove_event(System& system, unsigned id)
{
    for (Entry& entry : system.events)
    {
        for (std::size_t i { 0 }; i < entry.second.size(); ++i)
        {
            if (entry.second[i].id == id)
            {
                std::swap(entry.second[i], entry.second.back());
                entry.second.pop_back();
            }
        }
    }
}

// A helper function that should never be called by the user. This
// function will trigger all events registered to the specified event
// type.
void trigger_event(System& system, Event_Type type)
{
    for (Entry& entry : system.events)
    {
        if (entry.first == type)
        {
            for (Event event : entry.second)
            {
                trigger(event);
            }
        }
    }
}

// Function used to trigger all so called USER events.
void trigger_user(System& system)
{
    trigger_event(system, USER);
}

// This function MUST be called whenever system is destroyed. We can
// think of it like a destructor.

// Wishlist:

// - Hopefully this can be called automatically whenever 'system'
//   falls out of scope.

// - There seems to be memory leaks here? It never actually
//   deallocates any of the Action objects stored in the inside the
//   events. It might be a good idea to make Event automatically deal
//   with that somehow.... Hopefully it can deal with 'multi' actions
//   as well.

void destroy(System& system)
{
    trigger_event(system, EXIT);
}

// When using this event system it is important that the user does IO
// operations through the 'read' and 'write' functions, since these
// are the IO operations that trigger the IO events.

// Wishlist:

// - Maybe 'read' and 'write' should be able to deal with arbitrary
//   data. In the current implementation they only deal with strings.

void write(System& system, std::ostream& os, std::string const& message)
{
    os << message;
    trigger_event(system, IO);
}

std::string read(System& system, std::istream& is)
{
    std::string result { };
    std::getline(is, result);
    
    trigger_event(system, IO);
    
    return result;
}

/**** TESTCASES ****/

void callback_0(Action* action)
{
    std::cout << "CALLBACK 0 CALLED!" << std::endl;
}

void callback_1(Action* action)
{
    std::cout << "CALLBACK 1 CALLED!" << std::endl;
}

void callback_2(Action* action)
{
    std::cout << "CALLBACK 2 CALLED!" << std::endl;
}

bool predicate_0(Event const& event)
{
    return event.id % 2 == 0;
}

/* NOTE: This doesn't have to match exactly, but the functionality
 * itself of the program should be as close as you deems fit without
 * losing the fundamental features of the assignment. 

Expected output:

==== TEST #1 ====
Triggered: IO event triggered
==== TEST #2 ====
Triggered: IO event triggered
CALLBACK 0 CALLED!
==== TEST #3 ====
CALLBACK 2 CALLED!
Triggered: Multi in multi triggered!
CALLBACK 1 CALLED!
==== TEST #4 ====
Event #0: log
Event #1: log
Event #2: log
Event #4: callback
Event #3: [ callback [ log callback ] ]
==== TEST #5 ====
Removed event 2
CALLBACK 0 CALLED!
Event #1: log
Event #3: [ callback [ log callback ] ]
==== TEST #6 ====
Triggered: Bye bye!

*/

int main()
{
    System system { };

    unsigned event0 { register_event(system, EXIT, create_log("Adios!")) };
    unsigned event1 { register_event(system, EXIT, create_log("Bye bye!")) };
    
    unsigned event2 { register_event(system, IO, create_log("IO event triggered")) };

    std::cout << "==== TEST #1 ====" << std::endl;
    
    {
        std::ostringstream oss { };
        write(system, oss, "TEST");
        
        assert( oss.str() == "TEST");
    }

    std::vector<Action*> inner_multi {
        create_log("Multi in multi triggered!"),
        create_callback(callback_1)
    };

    std::vector<Action*> outer_multi {
        create_callback(callback_2),
        create_multi(inner_multi)
    };
    
    unsigned event3 { register_event(system, USER, create_multi(outer_multi)) };    
    unsigned event4 { register_event(system, IO, create_callback(callback_0)) };

    // would be nice if we could do something like this:
    
    // auto callback { [&system, event0](Action*) { remove_event(system, event0); } };
    // unsigned event_id { register_event(system, IO, create_callback(callback)) };

    std::cout << "==== TEST #2 ====" << std::endl;
    
    {
        std::istringstream iss { "hello there" };
        assert( (read(system, iss) == "hello there") );
    }

    std::cout << "==== TEST #3 ====" << std::endl;
    
    trigger_user(system);

    std::cout << "==== TEST #4 ====" << std::endl;
    
    print(system, std::cout);

    std::cout << "==== TEST #5 ====" << std::endl;
    
    remove_event(system, event2);
    
    write(system, std::cout, "Removed event 2\n");

    // Will remove every event with an even id
    remove_event(system, predicate_0);

    print(system, std::cout);

    std::cout << "==== TEST #6 ====" << std::endl;
    
    destroy(system);
}
