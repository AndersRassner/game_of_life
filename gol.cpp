// TODO: run sort on this once the internet returns
#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <random>
#include "GameBoard.hpp"
#include <chrono>
#include <thread>

using std::cout, std::cerr, std::endl;

int main(int argc, char * argv[]) {
  using namespace std::chrono_literals;
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

  GameBoard board120{30, 40};
  board120.print();
  auto start = std::chrono::system_clock::now();
  while(board120.getNoCells() > 0
	&& std::chrono::system_clock::now() < (start+30s)) {
    board120.next_board_state();
    board120.print();
    std::this_thread::sleep_for(500ms);
  }
  
  return 0;
}
