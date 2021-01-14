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

// - There are a lot of comments in this file, read them.

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <utility>

// This enum represents the different types of messages that can be
// handled in the messaging system. These are:

// - None: An empty message, doesn't contain any data.

// - Text: A message which contains a string (without the '#'
//         character).

// - Integer: A message which contains a single integer value.

// - Floating: A message which contains a single floating-point
//   (double) value.

// - Composite: A message which consists of several submessages.

enum Message_Type
{
    None,
    Text,
    Integer,
    Floating,
    Composite
};

// This struct represents a message that can be sent or
// recieved. There are four types of messages (see above) determined
// by 'type'.

// 'text' is used for Text messages. It contains the actual string
// (text) content.

// 'integer' is used for Integer messages. It contains the integer
// value.

// 'floating' is used for Floating messages. It contains the
// floating-point value.

// 'submessages' is a vector of messages that are used in Composite
// messages.

// Wishlist:

// - It would be a good idea to represent the 'type' in some other way.

// - It should be easy to add other types of messages.

// - Would be nice if 'integer' could be other types as well, for
//   example float, double, bool and other types that has operator<<.

// - Can we store only the relevant data member for the corresponding
//   type somehow?

struct Message
{
    Message_Type type { None };
    
    std::string text;
    int integer;
    double floating;
    std::vector<Message*> submessages;
};


// This function takes a 'Message' and returns an integer value which
// will be encoded to represent the type of the message.

int encode_type(Message const* message)
{
    if (message->type == None)
    {
        return 0;
    }
    else if (message->type == Text)
    {
        return 1;
    }
    else if (message->type == Integer)
    {
        return 2;
    }
    else if (message->type == Floating)
    {
        return 3;
    }
    else if (message->type == Composite)
    {
        return 4;
    }
    return -1;
}

// This function constructs a string encoding of the given 'message'
// and prints it to 'os'. This representation contains all the
// relevant information about the message. I.e. it will have the format:

// [type] [data]

// Where [type] is replaced by an integer which represents which type
// it is (see encode_type).

// [data] depends on the type:

// - None: [data] is empty

// - Text: [data] is a string (which contains no '#' except at the
//         end). The character '#' is meant to represent the end of
//         the string, which makes it easier to deserialize.

// - Integer: [data] is a string representation of the integer value

// - Floating: [data] is a string representation of the floating-point value

// - Composite: [data] has the format:
//              [count] [message(s)]

//              Where [count] is an integer representing how many
//              submessages this message contains.

//              [message(s)] consists of [count] number of messages in
//              a sequence.

//              For example:

//              2 1 this is my string# 3 5.6

//              Translates to: 2 submessages, the first one is a Text
//              (1 represents Text) message which contains the string
//              "This is my string" and the second one is a Floating
//              (3 represents Floating) message containing the value
//              "5.6".

// Whishlist:

// - Would be nice if we didn't have to check the type of the message.

// - Can we iterate through 'submessages' in any other way? With some
//   algorithm maybe?

void serialize_message(std::ostream& os, Message const* message)
{
    os << encode_type(message) << " ";
    if (message->type == Text)
    {
        os << message->text << "# ";
    }
    else if (message->type == Integer)
    {
        os << message->integer << " ";
    }
    else if (message->type == Floating)
    {
        os << message->floating << " ";
    }
    else if (message->type == Composite)
    {
        os << message->submessages.size() << " ";
        for (Message const* submessage : message->submessages)
        {
            serialize_message(os, submessage);
        }
    }
}

// Constructors for each message type.

// Wishlist:

// - These should be actual constructors for different types (a type
//   for each message type).

Message* construct_none()
{
    Message* result { new Message };
    result->type = None;
    return result;
}

Message* construct_text(std::string const& str)
{
    Message* result { new Message };
    result->type = Text;
    result->text = str;
    return result;
}

// Wishlist:

// - This + construct_floating could be merged into one function if the
// - there was a message which could store any arbitrary type.
Message* construct_integer(int value)
{
    Message* result { new Message };
    result->type = Integer;
    result->integer = value;
    return result;
}

Message* construct_floating(double value)
{
    Message* result { new Message };
    result->type = Floating;
    result->floating = value;
    return result;
}

Message* construct_composite(std::vector<Message*> const& submessages)
{
    Message* result { new Message };
    result->type = Composite;
    result->submessages = submessages;
    return result;    
}

// Destructor for messages.

// Wishlist:

// - Would be nice if this was a real destructor
void destroy_message(Message* message)
{
    if (message->type == Composite)
    {
        for (std::size_t i { 0 }; i < message->submessages.size(); ++i)
        {
            delete message->submessages[i];
        }
    }
}

// This class is a so called "message terminal" which contains a
// collection of messages. Think of it as an inbox of messages.

// The purpose of collecting them like this is because we want to be
// able to sort and filter messages.

// Wishlist:

// - Maybe all the operations relating to the Terminal should be
//   member functions instead.
struct Terminal
{
    std::string name;
    std::vector<Message*> messages { };
};

// Destructor for terminals.

// Wishlist:

// - Would be nice if this was a real destructor
void destroy_terminal(Terminal& terminal)
{
    for (std::size_t i { 0 }; i < terminal.messages.size(); ++i)
    {
        destroy_message(terminal.messages[i]);
        delete terminal.messages[i];
    }
}

void add_message(Terminal& terminal, Message* message)
{
    terminal.messages.push_back(message);
}

// This function prints a string representation of the entire contents
// of the passed in terminal, on the following format:

// [name] [count] [messages]

// Where [name] is replaced with 'terminal.name'

// [count] is the replaced with the number of messages in the terminal.

// [messages] is a list of [count] messages all printed with 'serialize_message'.
void serialize_terminal(std::ostream& os, Terminal const& terminal)
{
    os << terminal.name << " ";
    os << terminal.messages.size() << " ";

    for (std::size_t i { 0 }; i < terminal.messages.size(); ++i)
    {
        serialize_message(os, terminal.messages[i]);
    }
}

// 'sort_messages' return a new vector of messages which have been
// sorted according to the passed in Comparator (function which takes
// two messages 'a' and 'b' which then return true if 'a' should be
// sorted before 'b' and false otherwise)

// Wishlist:

// - Would be nice if the Comparator could be any callable object, not
//   just functions.

// - Maybe there is a better way to sort this?
using Comparator = bool(*)(Message const*, Message const*);
std::vector<Message*> sort_messages(Terminal& terminal, Comparator comparator)
{
    std::vector<Message*> result { terminal.messages };

    // Bubble sort
    for (std::size_t i { 0 }; i < result.size(); ++i)
    {
        for (std::size_t j { result.size() - 1 }; j > i; --j)
        {
            if (!comparator(result[j - 1], result[j]))
            {
                std::swap(result[j - 1], result[j]);
            }
        }
    }

    return result;
}

// 'filter_messages' return a new vector of messages where certain
// messages have been removed. Which messages are removed is
// determined by the passed in Predicate (function that takes a
// message and return true if that message should be removed and false
// otherwise).

// Wishlist:

// - Would be nice if the Predicate could be any callable object, not
//   just functions.

// - Maybe there is a better way? We only copy if the Predicate is false.

using Predicate = bool(*)(Message const*);
std::vector<Message*> filter_messages(Terminal& terminal, Predicate predicate)
{
    std::vector<Message*> result { };
    for (std::size_t i { 0 }; i < terminal.messages.size(); ++i)
    {
        Message* message { terminal.messages[i] };
        if (!predicate(message))
        {
            result.push_back(message);
        }
    }
    return result;
}

/*** TESTCASES ***/

/* Expected output:

My Terminal 7 0 1 This string is my message# 2 12 3 3.14 0 1 More text# 4 3 1 1# 3 2.3 2 45 
========
0 
0 
1 This string is my message# 
1 More text# 
2 12 
3 3.14 
4 3 1 1# 3 2.3 2 45 
========
0 
1 This string is my message# 
0 
1 More text# 
4 3 1 1# 3 2.3 2 45 

*/

bool comp(Message const* a, Message const* b)
{
    return encode_type(a) < encode_type(b);
}

bool pred(Message const* msg)
{
    int type { encode_type(msg) };
    return type == 2 || type == 3;
}

int main()
{
    Terminal terminal { "My Terminal" };

    // create some messages
    add_message(terminal, construct_none());
    add_message(terminal, construct_text("This string is my message"));
    add_message(terminal, construct_integer(12));
    add_message(terminal, construct_floating(3.14));
    add_message(terminal, construct_none());
    add_message(terminal, construct_text("More text"));

    // create a composite message
    std::vector<Message*> messages {
        construct_text("1"),
        construct_floating(2.3),
        construct_integer(45)
    };
    add_message(terminal, construct_composite(messages));

    // check if we can serialize all the messages
    serialize_terminal(std::cout, terminal);
    std::cout << std::endl;

    std::cout << "========" << std::endl;

    // test the sort_messages function. We sort on the type of message.

    // Would be nice if we could do this:
    // sort_messages(terminal, [](Message* a, Message* b) { return return encode_type(a) > encode_type(b); });
    std::vector<Message*> sorted { sort_messages(terminal, comp) };
    for (Message const* message : sorted)
    {
        serialize_message(std::cout, message);
        std::cout << std::endl;
    }

    std::cout << "========" << std::endl;

    // test the filter_messages function. We remove all Integer and
    // Floating messages.

    // Would be nice if we could do this:
    // filter_messages(terminal, [](Message* a) { encode_type(a) > 1; });
    std::vector<Message*> filtered { filter_messages(terminal, pred) };
    for (Message const* message : filtered)
    {
        serialize_message(std::cout, message);
        std::cout << std::endl;
    }

    // Destroy all the messages in the terminal
    destroy_terminal(terminal);
}
