#include <memory>
#include <cmath>
#include <utility>
#include <iostream>

struct Square
{
    char file;
    int rank;
    std::pair<size_t, size_t> diff(Square s)
    {
        return { abs(s.file - file), abs(s.rank - rank) };
    }
};


int main()
{
    // A Pawn starts at A2, moves to A8 and becomes a queen then moves to D5 and D2
    // Should print 452
    Chess_Piece p{{'A', 2}, new Pawn_Behavior{}};
    p.move({'A', 4});
    std::cout << p.position().rank;
    p.move({'A', 5});
    p.move({'A', 6});
    p.move({'A', 7});
    p.move({'A', 8}); // Turns into a queen
    p.move({'D', 5});

    std::cout << p.position().rank;
    p.move({'D', 2});

    std::cout << p.position().rank << '\n';
}
