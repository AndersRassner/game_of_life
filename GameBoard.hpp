#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <random>


class GameBoard {

private:
  int rows{};
  int columns{};
  std::vector<int> _board{};

public:
  GameBoard(int width = 30, int height = 20)
    : rows(height), columns(width), _board(width * height)
  {randomize_board();};
  GameBoard(const GameBoard& rhs) = default;
  ~GameBoard() = default;
  GameBoard& operator=(const GameBoard & rhs) = default;

  void randomize_board();
  void print();
  void debug_print();
};


#endif // GAMEBOARD_H
