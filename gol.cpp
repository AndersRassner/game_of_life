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

  // create 20x30 gameboard
  GameBoard board{};

  //create 5x5 gameboard
  // GameBoard board55{5, 5};
  // board55.debug_print();

  return 0;
}
