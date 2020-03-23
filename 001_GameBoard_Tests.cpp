#include <catch/catch.hpp>
#include "GameBoard.hpp"

TEST_CASE( "Test that next_board_state sets new state", "[GameBoard]" ) {
  GameBoard board{3, 3};
  std::vector<int> oneCenteredCellBoard{0,0,0,0,1,0,0,0,0};
  board.set_state(oneCenteredCellBoard);
  REQUIRE( board.get_board() == oneCenteredCellBoard );
  
  std::vector<int> faultyOneCenteredCellBoard{0,0,0,0,0,1,0,0,0,0};
  board.set_state(faultyOneCenteredCellBoard);
  REQUIRE( board.get_board() == oneCenteredCellBoard );
  REQUIRE( board.get_board() != faultyOneCenteredCellBoard );
  
  std::vector<int> tauBoard{1,1,1,1,1,1,1,1,1};
  board.set_state(tauBoard);
  REQUIRE( board.get_board() == tauBoard );
}
