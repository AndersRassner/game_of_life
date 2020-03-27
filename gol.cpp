#include "GameBoard.hpp"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <thread>
#include <vector>

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
	&& std::chrono::system_clock::now() < (start+10s)) {
    board120.next_board_state();
    board120.print();
    std::this_thread::sleep_for(25ms);
  }
  
  return 0;
}
