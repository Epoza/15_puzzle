#include <iostream>
#include <vector>
#include <array>

// clear the previous game or other console messages
constexpr int g_consoleLines{25};

class Tile
{
private:
  int m_number{};

public:
  Tile() = default;
  explicit Tile(int number) : m_number(number)
  {
  }

  // tile of number 0 is the empty tile
  bool isEmpty() { return m_number == 0; };

  // return the tile number
  int getNum() { return m_number; };
};

// output the tile number
std::ostream &operator<<(std::ostream &out, Tile tile)
{
  if (tile.getNum() > 9) // two digits
    out << " " << tile.getNum() << " ";
  else if (tile.getNum() > 0) // single digit
    out << "  " << tile.getNum() << " ";
  else if (tile.getNum() == 0) // empty tile
    out << "   ";
  return out;
}

// Your code goes here
class Board
{
private:
  std::vector<std::vector<Tile>> m_gameboard{{Tile{1}, Tile{2}, Tile{3}, Tile{4}}, {Tile{5}, Tile{6}, Tile{7}, Tile{8}}, {Tile{9}, Tile{10}, Tile{11}, Tile{12}}, {Tile{13}, Tile{14}, Tile{15}, Tile{0}}};

public:
  Board() = default;

  // output the board
  friend std::ostream &operator<<(std::ostream &out, const Board &board)
  {
    for (int i{0}; i <= g_consoleLines; ++i)
    {
      std::cout << '\n';
    }
    // iterate through each row
    for (const auto &row : board.m_gameboard)
    {
      // iterate through each tile in the row
      for (const auto &tile : row)
      {
        out << tile;
      }
      out << '\n';
    }
    return out;
  };
};

int main()
{
  Board board{};
  std::cout << board;

  return 0;
}