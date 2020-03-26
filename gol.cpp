#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <random>
#include "GameBoard.hpp"
using std::cout, std::cerr, std::endl;

/********************************\
|     ADD TESTING YO!            |
\********************************/

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

  // create default gameboard
  GameBoard board{};
  board.print();
  board.next_board_state();
  board.print();

  std::vector<int> test_vector2{0,0,0,0,1,0,0,0,0};
  board.set_state(test_vector2);
  board.print();
  board.next_board_state();
  board.print();
  //create 5x5 gameboard
  // GameBoard board55{5, 5};
  // board55.debug_print();

  return 0;
}
