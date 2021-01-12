#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <iomanip>
#include <iostream>
using namespace std;
class Game
{
public:
  Game(string name, int min_players, int max_players)
      : game_name{name}, players{min_players, max_players}
  {
  }
  virtual bool choose() const
  {
    cout << "Enter number of players: ";
    int p;
    cin >> p;
    return (p >= players.first && p <= players.second);
  }
  virtual void print(ostream &os) const
  {
    bool single{players.first == players.second};
    os << game_type() << " " << quoted(name()) << " has "
       << players.first;
    if (!single)
    {
      os << "-" << players.second;
    }
    os << " player" << (single ? "" : "s");
  }
  virtual ~Game() = default;

  std::string name() const { return game_name; }

  Game(Game const &) = delete;
  Game &operator=(Game const &) = delete;

protected:
  virtual string game_type() const = 0;

private:
  std::string game_name;
  std::pair<int, int> players;
};

class Board_Game : public Game
{
public:
  Board_Game(std::string name, int min, int max, int board_x,
             int board_y)
      : Game{name, min, max}, board_size{board_x, board_y}
  {
  }

  bool choose() const override
  {
    if (!Game::choose())
    {
      return false;
    }
    cout << "The board size is " << size()
         << ". Do you have room for it? [Y/n]: ";
    char c{};
    cin >> c;
    return c != 'n' && c != 'N';
  }

  std::string size() const
  {
    ostringstream oss;
    oss << board_size.first << "x" << board_size.second;
    return oss.str();
  }

  void print(ostream &os) const override
  {
    Game::print(os);
    os << "\" with size " << size();
  }

private:
  std::pair<int, int> board_size;
  string game_type() const override { return "Board game"; }
};

class Cooperative : public Board_Game
{
public:
  Cooperative(std::string name, int min, int max, int x, int y,
              bool traitor = false)
      : Board_Game{name, min, max, x, y}, has_traitor{traitor}
  {
  }

  bool choose() const override
  {
    if (!Board_Game::choose())
    {
      return false;
    }
    cout << "Do you want a possibility of a traitor? [Y/n]: ";
    char c{};
    cin >> c;
    return c != 'n' && c != 'N';
  }

  void print(ostream &os) const override
  {
    Board_Game::print(os);
    if (has_traitor)
    {
      os << " with traitor";
    }
  }

private:
  bool has_traitor;
  string game_type() const override { return "Cooperative board game"; }
};

class Card_Game : public Game
{
public:
  Card_Game(std::string const &name, int min, int max,
            bool special_deck = false)
      : Game{name, min, max}, special{special_deck}
  {
  }
  void print(ostream &os) const override
  {
    Game::print(os);
    if (!special)
    {
      os << " needs normal deck";
    }
  }

private:
  bool special;
  string game_type() const override { return "Card game"; }
};

void select_game(vector<Game *> const &games)
{
  for (Game const *g : games)
  {
    if (g->choose())
    {
      g->print(cout);
      cout << endl;
    }
  }
}

int main()
{
  vector<Game *> games{
      new Cooperative{"Pandemic", 2, 5, 30, 50, true},
      new Board_Game{"Terra Mystica", 2, 4, 30, 50},
      new Cooperative{"Zombiecide", 1, 4, 50, 50, false},
      new Card_Game{"Solitaire", 1, 1},
      new Card_Game{"Bang", 3, 7, true}

  };
  select_game(games);
  for (Game *&g : games)
  {
    delete g;
    g = nullptr;
  }
}
