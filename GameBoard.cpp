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
  for(int cell{0}; cell < _board.size(); ++cell) {
    switch(_board.at(cell)) {
    case 0 : {
      // Any dead cell with exactly 3 live neighbours resurrects
      if (sumNeighbours(cell) == 3) {
	temp_state.at(cell) = 1;
      }
      break;
    }
    case 1 : {
      int neighbours = sumNeighbours(cell);
      // Any live cell with 0 or 1 live neighbours dies
      if (neighbours < 2) {
	temp_state.at(cell) = 0;
      }
      // Any live cell with more than 3 live neighbours dies
      else if(neighbours > 3) {
	temp_state.at(cell) = 0;
      }
      // Any live cell with 2 or 3 live neighbours stays alive
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
  set_state(temp_state);
  return;
};

int GameBoard::sumNeighbours(int cell) {
  const int decColumns = columns - 1;
  // count neighbours of cells around cell. Corner cases include corners (haha)
  // and the outer rows & columns.
  if(cell < decColumns // first row
     || cell % columns == 0 // first column
     || cell % columns == decColumns // last column
     || cell >= (rows-1)*columns ){ // last row
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
  const int decColumns = columns - 1;
  if(cell == 0) {
    cout << "upper left corner" << endl;
    // upper left corner
    sum = std::accumulate(std::cbegin(_board),
			  std::cbegin(_board)+2, sum);
    sum = std::accumulate(std::cbegin(_board)+columns,
			  std::cbegin(_board)+columns+2, sum);
  }
  else if(cell == rows*columns-1) {
    cout << "lower right corner" << endl;
    // lower right corner
    sum = std::accumulate(std::crbegin(_board),
			  std::crbegin(_board)+2, sum);
    sum = std::accumulate(std::crbegin(_board)+columns,
			  std::crbegin(_board)+columns+2, sum);
  }
  else if(cell == decColumns) {
    cout << "upper right corner" << endl;
    // upper right corner
    sum = std::accumulate(std::cbegin(_board)+columns-2,
			  std::cbegin(_board)+columns, sum);
    sum = std::accumulate(std::cbegin(_board)+(columns*2)-2,
			  std::cbegin(_board)+(columns*2), sum);
  }
  else if(cell == rows*decColumns) {
    cout << "lower left corner" << endl;
    // lower left corner
    sum = std::accumulate(std::crbegin(_board)+columns-2,
			  std::crbegin(_board)+columns, sum);
    sum = std::accumulate(std::crbegin(_board)+(columns*2)-2,
			  std::crbegin(_board)+(columns*2), sum);
  }
  else if(cell % columns == decColumns) { // corners already covered
    cout << "last column" << endl;
    sum = std::accumulate(std::cbegin(_board)+cell-columns-1,
			  std::cbegin(_board)+cell-columns+1, sum);
    sum = std::accumulate(std::cbegin(_board)+cell-1,
			  std::cbegin(_board)+cell+1, sum);
    sum = std::accumulate(std::cbegin(_board)+cell+decColumns,
			  std::cbegin(_board)+cell+decColumns+2, sum);
  }else if(cell >= (rows-1)*columns){
    cout << "last row" << endl;
    sum = std::accumulate(std::cbegin(_board)+cell-columns-1,
			  std::cbegin(_board)+cell-columns+2, sum);
    sum = std::accumulate(std::cbegin(_board)+cell-1,
			  std::cbegin(_board)+cell+2, sum);
  }else if(cell % columns == 0) {
    cout << "first column" << endl;
    sum = std::accumulate(std::cbegin(_board)+cell-columns,
			  std::cbegin(_board)+cell-columns+2, sum);
    sum = std::accumulate(std::cbegin(_board)+cell,
			  std::cbegin(_board)+cell+2, sum);
    sum = std::accumulate(std::cbegin(_board)+cell+columns,
			  std::cbegin(_board)+cell+columns+2, sum);
  }else if(cell < columns){
    cout << "first row" << endl;
    sum = std::accumulate(std::cbegin(_board)+cell-1,
			  std::cbegin(_board)+cell+2, sum);
    sum = std::accumulate(std::cbegin(_board)+cell+decColumns,
			  std::cbegin(_board)+cell+decColumns+3, sum);
  }
  
  /* FOR EASIER LOOKUP
  if(cell < decColumns // first row
     || cell % columns == 0 // first column
     || cell % columns == decColumns // last column
     || cell >= (rows-1)*columns ){ // last row
  */
  cout << "final sum for cell " << cell << " is: " << sum << endl;
  return sum;
};
int GameBoard::simpleSum(int cell) {
  int sum = 0 - _board.at(cell); // we will count ourselves
  sum = std::accumulate(std::cbegin(_board)+cell-columns-1,
			std::cbegin(_board)+cell-columns+2, sum);
  sum = std::accumulate(std::cbegin(_board)+cell-1,
			std::cbegin(_board)+cell+2, sum);
  sum = std::accumulate(std::cbegin(_board)+cell+columns-1,
			std::cbegin(_board)+cell+columns+2, sum);
  cout << "final sum for cell " << cell << " is: " << sum << endl;
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
