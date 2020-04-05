#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

class GameBoard {
public:
  GameBoard(unsigned int width = 3, unsigned int height = 3)
      : rows(height), columns(width), _board(width * height) {
    randomize_board();
  };
  GameBoard(const GameBoard &rhs) = default;
  ~GameBoard() = default;
  GameBoard &operator=(const GameBoard &rhs) = default;

  void print();
  void next_board_state();
  void set_state(std::vector<int> new_state);
  int getNoCells();
  // Catch2 function
  std::vector<int> get_board() { return _board; };

private:
  unsigned int rows{};
  unsigned int columns{};
  std::vector<int> _board{};

  void randomize_board();
  int cornerSum(const unsigned int cell);
  int borderSum(const unsigned int cell);
  int simpleSum(const unsigned int cell);
  int complicatedSum(const unsigned int cell);
  int sumNeighbours(unsigned int cell);
};

#endif // GAMEBOARD_H
