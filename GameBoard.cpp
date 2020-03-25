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
  for( int& cell : _board) {
    cell = (dist(gen) <=5 ) ? 0 : 1;
  }
};

void GameBoard::next_board_state() {
  std::vector<int> temp_state = _board;
  // TODO: stuff that computes next state here by looking at _board and changing
  //       temp_state
  int cell{-1};
  for(int row{0}; row < rows; ++row) {
    for(int column{0}; column < columns; ++column) {
      cell += 1;
      switch(_board.at(cell)) {
      case 0 : {
	// TODO: Any dead cell with exactly 3 live neighbours resurrects
	if (sumNeighbours(cell) == 3) {
	  temp_state.at(cell) = 1;
	}
	break;
      }
      case 1 : {
	int neighbours = sumNeighbours(cell);
	// TODO: Any live cell with 0 or 1 live neighbours dies
	if (neighbours < 2) {
	  temp_state.at(cell) = 0;
	}
	// TODO: Any live cell with more than 3 live neighbours dies
	else if(neighbours > 3) {
	  temp_state.at(cell) = 0;
	}
	// TODO: Any live cell with 2 or 3 live neighbours stays alive
	else {
	  temp_state.at(cell) = 1;
	}
	break;
      }
      default : {
	cerr << "A cell should only have a value of 0 or 1" << endl;
      }
      }

    }
  }
  set_state(temp_state);
  return;
};
int GameBoard::sumNeighbours(int cell) {
  int decColumns = columns - 1;
  // count neighbours of cells around cell. Corner cases include corners (haha)
  // and the outer rows & columns.
  if(cell < decColumns // first row
     || cell % columns == 0 // first column
     || cell % columns == decColumns // last column
     || cell >= rows*decColumns ){ // last row
    cout << "cell " << cell << " is complicated" << endl;
    return complicatedSum(cell);
  }
  else{
    cout << "cell " << cell << " is simple" << endl;
    return simpleSum(cell);
  }
};
int GameBoard::complicatedSum(int cell) {
  int sum = 0 - _board.at(cell); // we will count ourselves
  if(cell == 0) {
    sum = std::accumulate(std::begin(_board),
			  std::begin(_board)+1, sum);
    cout << "sum is: " << sum << endl;
    sum = std::accumulate(std::begin(_board)+columns,
			  std::begin(_board)+columns+1, sum);
    cout << "sum is: " << sum << endl;
  }
  else if(cell == rows*columns-1) {
    sum = std::accumulate(std::rbegin(_board),
			  std::rbegin(_board)+1, sum);
    cout << "cell " << cell <<  endl << "sum is: " << sum << endl;
    sum = std::accumulate(std::rbegin(_board)+columns,
			  std::rbegin(_board)+columns+1, sum);
    cout << "sum is: " << sum << endl;
  }

  return sum;
};
int GameBoard::simpleSum(int cell) {
  int sum = 0 - _board.at(cell); // we will count ourselves
  cout  << "sum is: " << sum << endl;
  sum = std::accumulate(std::begin(_board)+cell-columns,
			std::begin(_board)+cell-columns+3, sum);
  cout << "sum is: " << sum << endl;
  sum = std::accumulate(std::begin(_board)+cell-1,
			std::begin(_board)+cell+1, sum);
  cout << "sum is: " << sum << endl;
  sum = std::accumulate(std::begin(_board)+cell+columns,
			std::begin(_board)+cell+columns+3, sum);
  cout << "final sum is: " << sum << endl;
  return sum;
};

void GameBoard::set_state(std::vector<int> new_state) {
  if(new_state.size() != rows*columns) { // this doesn't check rows == new_rows
    std::cerr << "new state doesn't have the same number "
	      << "of cells as current state" << endl
	      << "new state has size "
	      << new_state.size() << " compared to " << rows*columns
	      << endl;
    return;
  }
  _board = new_state;
  return;
}
