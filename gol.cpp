#include "GameBoard.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
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
  cout << "argc: " << argc << endl;
  for(int i{0}; i < argc ; ++i) {
    cout << "argument " << i+1 << ": " << argv[i] << endl;
  }

  if(argc == 1) { // create default gameboard
    GameBoard board120{30, 40};
    board120.print();
    auto start = std::chrono::system_clock::now();
    while(board120.getNoCells() > 0
	  && std::chrono::system_clock::now() < (start+10s)) {
      board120.next_board_state();
      board120.print();
      std::this_thread::sleep_for(100ms);
    }
  }
  else if(argc == 2) { // create board from file
    std::ifstream ifs(argv[1]);
    int rows {0};
    int columns {0};
    ifs >> columns;
    ifs >> rows;
    GameBoard board{columns, rows};
    std::vector<int> stateFromFile{};
    int x{0}; // TODO: replace with algorithm
    while(ifs >> x) {
      cout << "read: " << x << endl;
      stateFromFile.push_back(x);
    }
    auto start = std::chrono::system_clock::now();
    board.set_state(stateFromFile);
    board.next_board_state();
    board.print();
    // std::this_thread::sleep_for(2s);
    while(std::chrono::system_clock::now() < (start+8s)) {
      board.next_board_state();
      board.print();
      std::this_thread::sleep_for(100ms);
    }
  }



  return 0;
}
