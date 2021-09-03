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


#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <sstream>
#include <vector>

// This enum represents the different types of fields that can be used
// in the forms library,

// - DATA: A single floating point number.

// - TEXT: A line of text.

// - COLLECTION: A collection of floating point values.

enum Field_Type
{
    DATA,
    TEXT,
    COLLECTION
};

// A struct representing a form field. This field can be one of three
// different types (see above). Each type has its own data member in
// the struct.

// Wishlist:

// - It would be a good idea to represent the 'type' in some other way.

// - It should be easy to add other types of fields.

// - Right now DATA and COLLECTION only stores floating point
//   values. Would be nice if they could store other types as well.

// - Can 'collection' be represented in a better way than a vector?

struct Field
{
    Field_Type type { TEXT };

    double data;
    std::string text;
    std::vector<double> collection;
};

// Function used to create a field
Field* create_field(Field_Type type)
{
    return new Field{type};
}

// Function used to prompt the user for the value(s) of 'field'. Each
// prompt will be written to 'os' and the values will be filled in by
// the user from 'is'.

// Wishlist:

// - Would be nice if we didn't have to manually check the type of the
//   field.

// - Maybe the COLLECTION case can be simplified or clarified in some
//   way?
void fill(Field* field, std::ostream& os, std::istream& is)
{
    if (field->type == DATA)
    {
        os << "(data): ";
        while ( !(is >> field->data) )
        {
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max());
            os << "Error: Try again: ";
        }
    }
    else if (field->type == TEXT)
    {
        os << "(text): ";
        std::getline(is, field->text);
    }
    else if (field->type == COLLECTION)
    {
        os << "(values, press ctrl+D when done): ";
        double value { };
        while (is >> value)
        {
            for (unsigned i { 0 }; i < field->collection.size(); ++i)
            {
                if (field->collection[i] == value)
                {
                    return;
                }
            }
            field->collection.push_back(value);
        }
        is.clear();
    }
}

// Function used to print a filled out field to the stream 'os'.

// Wishlist:

// - Would be nice if we didn't have to manually check the type of the
//   field.

// - Maybe the COLLECTION case can be simplified or clarified in some
//   way?
void print(Field* field, std::ostream& os)
{
    if (field->type == DATA)
    {
        os << field->data;
    }
    else if (field->type == TEXT)
    {
        os << '\"' << field->text << '\"';
    }
    else if (field->type == COLLECTION)
    {
        os << "[ ";
        for (unsigned i { 0 }; i < field->collection.size(); ++i)
        {
            os << field->collection[i] << ' ';
        }
        os << "]";
    }
}

// Entry represents a complete field entry in the form. That is a
// field name + a field.
using Entry = std::pair<std::string, Field*>;

// Form represents a complete form that can be filled out and printed
// by a user. A Form has a name and a collection of fields (associated
// with names). Notice that duplicate field names are allowed right now.

// Wishlist:

// - Maybe 'fields' can be represented in another way?

// - It shouldn't be possible to modify 'fields' in any way except
// - through the 'add' function below.

// - This object might cause memory leaks. That should probably be
//   fixed.
struct Form
{
    std::string name;
    std::vector<Entry> fields { };
};

// Helper function used to add fields to a form.
void add(Form& form, std::string const& name, Field* field)
{
    form.fields.emplace_back(name, field);
}

// 'fill' is used to prompt the user to fill out the entire form. The
// prompts will be printed to 'os' and the field values will be
// entered by the user via 'is'.

// Wishlist:

// - Maybe we can iterate through the fields in a better way?

// - Would be nice if we could implement 'fill' like this:
// {
//     auto f = [&is](Field* field, std::ostream& os)
//              {
//                  fill(field, os, is);
//              };
    
//     iterate(form, os, f);
// }
// This would require you to implement 'iterate'.

void fill(Form& form, std::ostream& os, std::istream& is)
{
    os << form.name << std::endl << std::endl;
    for (int i { 0 }; i < form.fields.size(); ++i)
    {
        Entry entry { form.fields[i] };
        os << entry.first << " ";
        fill(entry.second, os, is);
        os << std::endl;
    }
}

// 'print' is used to print a filled out form to 'os'.

// Wishlist:

// - Maybe we can iterate through the fields in a better way?

// - Would be nice if we could implement 'print' like this:
// {
//     auto f = [](Field* field, std::ostream& os)
//              {
//                  print(field, os);
//              };
    
//     iterate(form, os, f);
// }
// This would require you to implement 'iterate'.

void print(Form const& form, std::ostream& os)
{
    os << form.name << std::endl << std::endl;
    for (int i { 0 }; i < form.fields.size(); ++i)
    {
        Entry entry { form.fields[i] };
        os << entry.first << ": ";
        print(entry.second, os);
        os << std::endl;
    }
}

// Example of how we can use this library.

/* Expected output:

Product information

Product (text): 
Price (data): 
Measurements (values, press ctrl+D when done): 
========================
Product information

Product: "Used Car"
Price: 39600.5
Measurements: [ 12.5 13.7 -7.5 ]
*/

// Note that the prints above the equal signs are the prompts from
// 'fill', but the values that were entered does not appear since they
// are filled in through a stringstream rather than a terminal.

int main()
{
    Form form { "Product information" };

    add(form, "Product", create_field(TEXT));
    add(form, "Price", create_field(DATA));
    add(form, "Measurements", create_field(COLLECTION));

    // Simulate "std::cin" without having to enter values manually
    std::istringstream iss { "Used Car\n39600.50\n12.5 13.7 -7.5 12.5" };
    
    fill(form, std::cout, iss);

    std::cout << "========================" << std::endl;
    
    print(form, std::cout);
}
