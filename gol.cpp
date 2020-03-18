#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>

using std::cout, std::cerr, std::endl;

class GameBoard {
public:
  //constructor
  GameBoard(int width = 0, int height = 0)
    : rows(height), columns(width), _board(width * height) {};
  //defaulted copy constructor
  GameBoard(const GameBoard& rhs) = default;
  //defaulted destructor
  ~GameBoard() = default;
  //defaulted copy operator
  GameBoard& operator=(const GameBoard & rhs) = default;

  void print() {
    cout << "{";
    for (int row{0}; row < rows; ++row) {
      copy(std::begin(_board)+row, std::begin(_board)+row+columns, std::ostream_iterator<int>{cout, ","});
      cout << endl;
    }
    cout << "}" << endl;
  };
private:
  int rows{};
  int columns{};
  std::vector<int> _board{};
};

int main(int argc, char * argv[]) {
  int expectedArguments{1};
  cout << "argc: " << argc << endl;
  for(int i{0}; i < argc ; ++i) {
    cout << "argument " << i+1 << ": " << argv[i] << endl;
  }
  
  if(!(argc == expectedArguments)) {
    std::cerr << "please pass " << expectedArguments
	      << "when running me" << std::endl;
  }

  // create 0x0 gameboard
  GameBoard board{};

  //create 5x5 gameboard
  GameBoard board55{5, 5};

  board55.print();

  return 0;
}
