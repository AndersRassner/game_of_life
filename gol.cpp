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
    : rows(std::vector<int>(height)), columns(std::vector<int>(width)) {};
  //defaulted copy constructor
  //defaulted destructor
  //defaulted copy operator
private:
  std::vector<int> rows{};
  std::vector<int> columns{};
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
  return 0;
}
