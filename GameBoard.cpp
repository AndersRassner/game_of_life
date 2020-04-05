#include "GameBoard.hpp"
using std::cout, std::cerr, std::endl;

void GameBoard::print() {
  cout << std::setfill('-') << std::setw(columns + 2) << "-" << '\n';
  for (unsigned int row{0}; row < rows; ++row) {
    cout << '|';
    std::transform(
        std::begin(_board) + row * columns,
        std::begin(_board) + row * columns + columns,
        std::ostream_iterator<char>{cout, ""},
        [](unsigned int cell) -> char { return (cell == 0) ? ' ' : '#'; });
    cout << '|' << '\n';
  }
  cout << std::setfill('-') << std::setw(columns + 2) << "-" << endl;
};

void GameBoard::randomize_board() {
  std::random_device rand_dev{};
  std::mt19937 gen(rand_dev());
  std::bernoulli_distribution dist(0.5);
  for (int &cell : _board) {
    cell = (dist(gen)) ? 0 : 1;
  }
};

void GameBoard::set_state(std::vector<int> new_state) {
  if (new_state.size() !=
      rows * columns) { // this doesn't check rows == new_rows
    std::cerr << "new state doesn't have the same number "
              << "of cells as current state" << endl
              << "new state has size " << new_state.size() << " compared to "
              << _board.size() << endl;
    return;
  }
  _board = new_state;
  return;
};

int GameBoard::getNoCells() {
  return std::accumulate(std::cbegin(_board), std::cend(_board), 0);
};

void GameBoard::next_board_state() {
  std::vector<int> temp_state = _board;
  for (unsigned int cell{0}; cell < _board.size(); ++cell) {
    switch (_board.at(cell)) {
    case 0: {
      // Any dead cell with exactly 3 live neighbours resurrects
      if (sumNeighbours(cell) == 3) {
        temp_state.at(cell) = 1;
      }
      break;
    }
    case 1: {
      int neighbours = sumNeighbours(cell);
      // Any live cell with 0 or 1 live neighbours dies
      if (neighbours < 2) {
        temp_state.at(cell) = 0;
      }
      // Any live cell with more than 3 live neighbours dies
      else if (neighbours > 3) {
        temp_state.at(cell) = 0;
      }
      // Any live cell with 2 or 3 live neighbours stays alive
      else {
        temp_state.at(cell) = 1;
      }
      break;
    }
    default: { cerr << "A cell should only have a value of 0 or 1" << endl; }
    }
  }
  set_state(temp_state);
  return;
};

int GameBoard::sumNeighbours(unsigned int cell) {
  const unsigned int decColumns = columns - 1;
  // count neighbours of cells around cell. Corner cases include corners (haha)
  // and the outer rows & columns.
  if (cell < decColumns                  // first row
      || cell % columns == 0             // first column
      || cell % columns == decColumns    // last column
      || cell >= (rows - 1) * columns) { // last row
    return complicatedSum(cell);
  } else {
    return simpleSum(cell);
  }
};

int GameBoard::complicatedSum(const unsigned int cell) {
  int sum = 0 - _board.at(cell); // we will count ourselves
  const unsigned int decColumns = columns - 1;

  if (cell == 0 || cell == rows * columns - 1 || cell == decColumns ||
      cell == rows * decColumns) {
    sum = cornerSum(cell);
  } else {
    sum = borderSum(cell);
  }

  return sum;
};

int GameBoard::cornerSum(const unsigned int cell) {
  const unsigned int decColumns = columns - 1;
  int sum = 0 - _board.at(cell); // we will count ourselves

  if (cell == 0) {
    // upper left corner
    sum = std::accumulate(std::cbegin(_board), std::cbegin(_board) + 2, sum);
    sum = std::accumulate(std::cbegin(_board) + columns,
                          std::cbegin(_board) + columns + 2, sum);
  } else if (cell == rows * columns - 1) {
    // lower right corner
    sum = std::accumulate(std::crbegin(_board), std::crbegin(_board) + 2, sum);
    sum = std::accumulate(std::crbegin(_board) + columns,
                          std::crbegin(_board) + columns + 2, sum);
  } else if (cell == decColumns) {
    // upper right corner
    sum = std::accumulate(std::cbegin(_board) + columns - 2,
                          std::cbegin(_board) + columns, sum);
    sum = std::accumulate(std::cbegin(_board) + (columns * 2) - 2,
                          std::cbegin(_board) + (columns * 2), sum);
  } else if (cell == rows * decColumns) {
    // lower left corner
    sum = std::accumulate(std::crbegin(_board) + columns - 2,
                          std::crbegin(_board) + columns, sum);
    sum = std::accumulate(std::crbegin(_board) + (columns * 2) - 2,
                          std::crbegin(_board) + (columns * 2), sum);
  }
  return sum;
};

int GameBoard::borderSum(const unsigned int cell) {
  const unsigned int decColumns = columns - 1;
  int sum = 0 - _board.at(cell); // we will count ourselves

  if (cell % columns == decColumns) {
    // right border
    sum = std::accumulate(std::cbegin(_board) + cell - columns - 1,
                          std::cbegin(_board) + cell - columns + 1, sum);
    sum = std::accumulate(std::cbegin(_board) + cell - 1,
                          std::cbegin(_board) + cell + 1, sum);
    sum = std::accumulate(std::cbegin(_board) + cell + decColumns,
                          std::cbegin(_board) + cell + decColumns + 2, sum);
  } else if (cell >= (rows - 1) * columns) {
    // lower border
    sum = std::accumulate(std::cbegin(_board) + cell - columns - 1,
                          std::cbegin(_board) + cell - columns + 2, sum);
    sum = std::accumulate(std::cbegin(_board) + cell - 1,
                          std::cbegin(_board) + cell + 2, sum);
  } else if (cell % columns == 0) {
    // left border
    sum = std::accumulate(std::cbegin(_board) + cell - columns,
                          std::cbegin(_board) + cell - columns + 2, sum);
    sum = std::accumulate(std::cbegin(_board) + cell,
                          std::cbegin(_board) + cell + 2, sum);
    sum = std::accumulate(std::cbegin(_board) + cell + columns,
                          std::cbegin(_board) + cell + columns + 2, sum);
  } else if (cell < columns) {
    // upper border
    sum = std::accumulate(std::cbegin(_board) + cell - 1,
                          std::cbegin(_board) + cell + 2, sum);
    sum = std::accumulate(std::cbegin(_board) + cell + decColumns,
                          std::cbegin(_board) + cell + decColumns + 3, sum);
  }
  return sum;
};

int GameBoard::simpleSum(const unsigned int cell) {
  int sum = 0 - _board.at(cell); // we will count ourselves
  sum = std::accumulate(std::cbegin(_board) + cell - 1 - columns,
                        std::cbegin(_board) + cell + 2 - columns, sum);
  sum = std::accumulate(std::cbegin(_board) + cell - 1,
                        std::cbegin(_board) + cell + 2, sum);
  sum = std::accumulate(std::cbegin(_board) + cell - 1 + columns,
                        std::cbegin(_board) + cell + 2 + columns, sum);
  return sum;
};
