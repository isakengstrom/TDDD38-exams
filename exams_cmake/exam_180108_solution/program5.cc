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

class Move_Behavior
{
public:
    virtual bool valid_move(Square, Square) const noexcept = 0;
    virtual ~Move_Behavior() = default;
    Move_Behavior(Move_Behavior const &) = delete;
    Move_Behavior() = default;
};

class Rook_Behavior : public Move_Behavior
{
public:
    bool valid_move(Square pos, Square s) const noexcept override
    {
        auto [file, rank] { pos.diff(s) };
        return file == 0 || rank == 0;
    }
};

class Queen_Behavior: public Rook_Behavior
{
public:
    bool valid_move(Square pos, Square s) const noexcept override
    {
        auto [file_diff, rank_diff] = pos.diff(s);
        return Rook_Behavior::valid_move(pos, s) || file_diff==rank_diff;
    }
};

class Pawn_Behavior: public Move_Behavior
{
public:
    bool valid_move(Square pos, Square s) const noexcept override
    {
        auto [file_diff, rank_diff] = pos.diff(s);
        bool rank_valid { rank_diff == 1 };
        if (is_first)
        {
            is_first = false;
            rank_valid = (rank_diff < 3);
        }
        return file_diff == 0 && rank_valid;
    }
    bool should_change(Square s) const
    {
        return s.rank == 8;
    }
private:
    mutable bool is_first {true};
};

class Chess_Piece
{
public:
    Chess_Piece(Square start, Move_Behavior const * m): pos{start}, current_behavior{m} {}
    void move(Square next)
    {
        if (current_behavior->valid_move(pos, next))
        {
            pos = next;
            if ( auto p = dynamic_cast<Pawn_Behavior const *>(current_behavior.get());
                    p && p->should_change(pos) )
            {
                current_behavior = std::make_unique<Queen_Behavior>();
            }
        }
    }
    Square position() const
    {
        return pos;
    }
    Chess_Piece & operator=(Chess_Piece const &) = delete;
    Chess_Piece(Chess_Piece const &)=delete;
private:
    Square pos;
    std::unique_ptr<Move_Behavior const> current_behavior;
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
