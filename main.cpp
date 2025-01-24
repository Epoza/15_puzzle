#include <iostream>
#include <vector>
#include <cassert>
#include <limits>
#include "Random.h"

// clear the previous game or other console messages
constexpr int g_consoleLines{25};

// convert a user inputted char to a specific direction
class Direction
{
public:
  enum Type
  {
    up,
    down,
    left,
    right,
    maxDirections
  };

  Direction(Type type) : m_type{type}
  {
  }

  Type getType() const
  {
    return m_type;
  }

  Direction operator-() const
  {
    switch (m_type)
    {
    case up:
      return Direction{down};
    case down:
      return Direction{up};
    case left:
      return Direction{right};
    case right:
      return Direction{left};
    default:
      break;
    }

    assert(0 && "Unsupported direction was passed!");
    return Direction{up};
  }

  static Direction getRandomDirection()
  {
    return Direction{static_cast<Type>(Random::get(0, Direction::maxDirections - 1))};
  }

private:
  Type m_type{};
};

std::ostream &operator<<(std::ostream &out, Direction d)
{
  switch (d.getType())
  {
  case Direction::up:
    return (out << "up");
  case Direction::down:
    return (out << "down");
  case Direction::left:
    return (out << "left");
  case Direction::right:
    return (out << "right");
  default:
    break;
  }

  assert(0 && "Unsupported direction was passed!");
  return (out << "unknown direction");
}

// get and validate user input
namespace UserInput
{
  bool isValid(char input)
  {
    return input == 'w' || input == 'a' || input == 's' || input == 'd' || input == 'q';
  }

  char getUserInput()
  {
    char input{};
    while (!isValid(input))
    {
      std::cout << "Please enter a command: ";
      std::cin >> input;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return input;
  }

  Direction convertToDirection(char input)
  {
    switch (input)
    {
    case 'w':
      return Direction{Direction::up};
    case 'a':
      return Direction{Direction::left};
    case 's':
      return Direction{Direction::down};
    case 'd':
      return Direction{Direction::right};
    }

    assert(0 && "Unsupported direction was passed!");
    return Direction{Direction::up};
  }
}

// stores a pair of coordinates for the board
struct Point
{
  int x{};
  int y{};

  friend bool operator==(const Point p1, const Point p2)
  {
    return (p1.x == p2.x) && (p1.y == p2.y);
  }

  friend bool operator!=(const Point p1, const Point p2)
  {
    return !(p1 == p2);
  }

  Point getAdjacentPoint(Direction d) const
  {
    switch (d.getType())
    {
    case Direction::up:
      return Point{x, y - 1};
    case Direction::down:
      return Point{x, y + 1};
    case Direction::left:
      return Point{x - 1, y};
    case Direction::right:
      return Point{x + 1, y};
    default:
      break;
    }
    assert(0 && "Unsupported direction was passed!");
    return *this;
  }
};

// class for a single game tile
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

// class for the board
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
  std::cout << std::boolalpha;
  std::cout << (Point{1, 1}.getAdjacentPoint(Direction::up) == Point{1, 0}) << '\n';
  std::cout << (Point{1, 1}.getAdjacentPoint(Direction::down) == Point{1, 2}) << '\n';
  std::cout << (Point{1, 1}.getAdjacentPoint(Direction::left) == Point{0, 1}) << '\n';
  std::cout << (Point{1, 1}.getAdjacentPoint(Direction::right) == Point{2, 1}) << '\n';
  std::cout << (Point{1, 1} != Point{2, 1}) << '\n';
  std::cout << (Point{1, 1} != Point{1, 2}) << '\n';
  std::cout << !(Point{1, 1} != Point{1, 1}) << '\n';

  return 0;
}