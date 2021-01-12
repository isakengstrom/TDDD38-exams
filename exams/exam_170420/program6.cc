#include <sstream>
#include <iterator>
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
using namespace std;

// Given, should not be changed
struct Image_Data
{
    Image_Data(string const & line)
    {
        istringstream iss{line};
        iss >> type;
        for ( int d; iss >> d; )
        {
            args.push_back(d);
        }
    }
    string type;
    vector<int> args;
};

// Add your classes here



/*
 * Given code. No modifications allowed unless specified!
 */
Image* error_printer(Image_Data const & d)
{
    cout << "!!! " << d.type << " is an invalid file format !!!\n";
    return nullptr;
}
int main()
{
    vector<unique_ptr<Image>> images;
    vector<function<Image*(Image_Data const &)>> funs { PNG::parse,
                                                        JPG::parse,
                                                        BMP::parse,
                                                        error_printer};
    cout << "Enter one line for each image on the format \"type [type specific data]\". Exit with \"q\".\n\n";

    for ( string line; getline(cin, line); )
    {
        if ( line == "q" )
        {
            break;
        }
        Image_Data data{line};
        for ( auto && f: funs )
        {
            if (auto ptr = f(data))
            {
                images.emplace_back(ptr);
                break;
            }
        }
    }

// Additions allowed below (calculate and print sum)




}
