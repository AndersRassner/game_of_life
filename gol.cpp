#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <random>
#include <thread>

using std::cout, std::cerr, std::endl;

class GameBoard {
public:
  //constructor
  GameBoard(int width = 0, int height = 0)
    : rows(height), columns(width), _board(width * height) {randomize_board();};
  //defaulted copy constructor
  GameBoard(const GameBoard& rhs) = default;
  //defaulted destructor
  ~GameBoard() = default;
  //defaulted copy operator
  GameBoard& operator=(const GameBoard & rhs) = default;

  void print() {
    if (rows == 0 || columns == 0) { return; } // can't print empty board
    for (int row{0}; row < rows; ++row) {
      cout << endl << ((row == 0) ? '{' : ' ');
      copy(std::begin(_board)+row, std::begin(_board)+row+columns-1,
	   std::ostream_iterator<int>{cout, ","});
      cout << _board.at(row+columns);
    }
    cout << "}" << endl;
  };
private:
  void randomize_board() {
    std::random_device rand_dev{};
    std::mt19937 gen(rand_dev());
    // 0,1 would be cleaner but only 50% would be possible. Could look
    // at distribution other than uniform but good enough for now
    std::uniform_int_distribution<> dist(1,10);
    cout << "board before randomization" << endl;
    print();
    for( int& cell : _board) {
      cell = (dist(gen) <=5 ) ? 0 : 1;
    }
    cout << "board after randomization" << endl;
    print();
  };
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
