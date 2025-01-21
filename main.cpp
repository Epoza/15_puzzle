#include <iostream>

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
    out << "  " << tile.getNum() << "  ";
  else if (tile.getNum() == 0) // empty tile
    out << "   ";
  return out;
}
int main()
{
  Tile tile1{10};
  Tile tile2{8};
  Tile tile3{0}; // the missing tile
  Tile tile4{1};

  std::cout << "0123456789ABCDEF\n"; // to make it easy to see how many spaces are in the next line
  std::cout << tile1 << tile2 << tile3 << tile4 << '\n';

  std::cout << std::boolalpha << tile1.isEmpty() << ' ' << tile3.isEmpty() << '\n';
  std::cout << "Tile 2 has number: " << tile2.getNum() << "\nTile 4 has number: " << tile4.getNum() << '\n';

  return 0;
}