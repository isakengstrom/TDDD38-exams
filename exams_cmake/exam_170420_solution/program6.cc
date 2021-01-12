#include <sstream>
#include <iterator>
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
using namespace std;

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

class Image
{
public:
    virtual ~Image() = default;
    virtual int size() = 0;
protected:
    Image(int w, int h): width{w}, height{h} {}
    int width, height;
};

class PNG : public Image
{
public:
    int size() override
    {
        return width*height*1.5;
    }
    static PNG* parse(Image_Data const & data)
    {
        if ( data.type != "PNG" )
            return nullptr;
        return new PNG{data.args[0], data.args[1]};
    }
private:
    PNG(int w, int h): Image{w,h} {}
};

class JPG: public Image
{
private:
    JPG(int w, int h, int c)
        : Image{w,h}, quality{c}
    {}
    int quality;
public:
    static JPG* parse(Image_Data const & d)
    {
        if (d.type != "JPG" )
            return nullptr;
        return new JPG{d.args[0], d.args[1], d.args[2]};
    }
    int size() override
    {
        return width*height*3*(quality/100.0);
    }

};
class BMP: public Image
{
private:
    BMP(int w, int h): Image{w,h} {}
public:
    static BMP* parse(Image_Data const & d)
    {
        if (d.type != "BMP" )
            return nullptr;
        return new BMP{d.args[0], d.args[1]};
    }
    int size() override
    {
        return width*height*3;
    }

};

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
    cout << "Enter one line for each image on the format \"type width height [extra data]\". Exit with \"q\".\n\n";

    for ( string line; getline(cin, line); )
    {
        if ( line == "q" )
            break;
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

    int tot {};
    for ( auto && ptr: images )
    {
        tot += ptr->size();
    }
    cout << "\nTotal size: " << tot << " bytes!\n";


}
