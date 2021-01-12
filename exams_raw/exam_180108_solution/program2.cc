#include <iterator>
#include <fstream>
#include <random>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

int main(int argc, char * argv[])
{
    if ( argc != 3 )
    {
        cout << "Start with IMAGE_SIZE FILENAME\n";
        return 1;
    }
    int max;
    try
    {
        max = stoi(argv[1]);
    }
    catch (std::exception const &)
    {
        cerr << "Invalid numerical value " << argv[1] << "\n";
        return 2;
    }
    if (max < 2 || max > 1000)
    {
        cerr << "IMAGE_SIZE must be in [2,1000]\n";
        return 3;
    }
    ofstream output_file { argv[2] };
    if ( !output_file )
    {
        cerr << "File \"" << argv[2] << "\" couldn't be opened\n";
        return 4;
    }

    int N { max*max };
    vector<int> vals (N);

    uniform_int_distribution<> dst{0,max-1};
    mt19937 eng{random_device{}()}; // or: random_device eng;
    generate(begin(vals), end(vals),
            [&eng, &dst](){return dst(eng);});

    vector<pair<int, int>> points ( N/2 ) ;

    transform(begin(vals), begin(vals)+(N/2),
              begin(vals)+(N/2),
              begin(points),
              [](int x, int y){return pair{y,x}; });

    sort(begin(points), end(points));

    points.erase(unique(begin(points), end(points)), end(points));

    vector<vector<bool>> image (max, vector<bool>(max));
    for_each(begin(points), end(points),
             [&image](auto p){image[p.first][p.second] = true;}
            );

    output_file << "P1\n" << max << " " << max << endl;
    for_each(begin(image), end(image),
            [&output_file](auto & line){
                copy(begin(line),end(line),ostream_iterator<bool>{output_file, " "});
                output_file << '\n';
            });
}
