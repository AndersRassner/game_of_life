#include "GameBoard.hpp"

using std::cout, std::cerr, std::endl;


void GameBoard::debug_print() {
  copy(std::begin(_board), std::end(_board),
       std::ostream_iterator<int>{cout, ","});
  cout << endl;
  if (rows == 0 || columns == 0) { return; } // can't print empty board
  for (int row{0}; row < rows; ++row) {
    // cout << " row: " << row << " at address: " << &(*(std::begin(_board)+row*columns)) << " to address: " << &(*(std::begin(_board)+row*columns+columns));
    cout << endl << ((row == 0) ? '{' : ' ');
    copy(std::begin(_board)+row*columns,
	 std::begin(_board)+row*columns+columns-1,
	 std::ostream_iterator<int>{cout, ","});
    cout << _board.at(row*columns+columns-1);
  }
  cout << "}" << endl;
  cout << std::setfill('-') << std::setw(columns+2) << "-" << endl;
  for (int row{0}; row < rows; ++row) {
    cout << '|';
    std::transform(std::begin(_board)+row*columns, std::begin(_board)+row*columns+columns,
		   std::ostream_iterator<char>{cout, ""},
		   [](int cell) -> char {return (cell == 0) ? ' ' : '#';});
    cout << '|' << endl;
  }
  cout << std::setfill('-') << std::setw(columns+2) << "-" << endl;
};

void GameBoard::print() {
  cout << std::setfill('-') << std::setw(columns+2) << "-" << endl;
  for (int row{0}; row < rows; ++row) {
    cout << '|';
    std::transform(std::begin(_board)+row*columns,
		   std::begin(_board)+row*columns+columns,
		   std::ostream_iterator<char>{cout, ""},
		   [](int cell) -> char {return (cell == 0) ? ' ' : '#';});
    cout << '|' << endl;
  }
  cout << std::setfill('-') << std::setw(columns+2) << "-" << endl;
};
void GameBoard::randomize_board() {
  std::random_device rand_dev{};
  // std::mt19937 gen(1);
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

GameBoard GameBoard::next_board_state() {
  cout << "next board is returned" << endl;
  GameBoard temp_board = *this;
  GameBoard next_board = temp_board;
  return next_board;
};


void GameBoard::set_state(std::vector<int> new_state) {
  if(new_state.size() != rows*columns) {
    std::cerr << "new state doesn't have the same number "
	      << "of cells as current state" << endl
	      << "new state has size "
	      << new_state.size() << " compared to " << rows*columns
	      << endl;
    return;
  }
  std::cout << "yo let's say it worked" << endl;
  return;
}
