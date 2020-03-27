#include <catch/catch.hpp>
#include "GameBoard.hpp"

TEST_CASE( "Test that the next_board_state for known patterns correctly flips between known states",
	   "[GameBoard]" ) {
  GameBoard board{6, 6};

  SECTION("toad steps back and forth correctly") {
    std::vector<int> toad
      {0,0,0,0,0,0,
       0,0,0,0,0,0,
       0,0,1,1,1,0,
       0,1,1,1,0,0,
       0,0,0,0,0,0,
       0,0,0,0,0,0,
      };
    std::vector<int> toadStepped
      {0,0,0,0,0,0,
       0,0,0,1,0,0,
       0,1,0,0,1,0,
       0,1,0,0,1,0,
       0,0,1,0,0,0,
       0,0,0,0,0,0,
      };

    board.set_state(toad);
    board.next_board_state();
    CHECK( board.get_board() == toadStepped );
    board.next_board_state();
    CHECK( board.get_board() == toad );
  };
  SECTION( "blinker blinks correctly" ) {
    std::vector<int> blinker
      {0,0,0,0,0,0,
       0,1,1,0,0,0,
       0,1,1,0,0,0,
       0,0,0,1,1,0,
       0,0,0,1,1,0,
       0,0,0,0,0,0,
      };
    std::vector<int> blinkerStepped
      {0,0,0,0,0,0,
       0,1,1,0,0,0,
       0,1,0,0,0,0,
       0,0,0,0,1,0,
       0,0,0,1,1,0,
       0,0,0,0,0,0,
      };
    board.set_state(blinker);
    board.next_board_state();
    CHECK( board.get_board() == blinkerStepped );
    board.next_board_state();
    CHECK( board.get_board() == blinker );
    
  };
  SECTION( "glider glides correctly" ) {
    std::vector<int> glider
      {0,0,0,0,0,0,
       0,0,1,0,0,0,
       0,0,0,1,0,0,
       0,1,1,1,0,0,
       0,0,0,0,0,0,
       0,0,0,0,0,0,
      };
    std::vector<int> gliderStepped
      {0,0,0,0,0,0,
       0,0,0,0,0,0,
       0,1,0,1,0,0,
       0,0,1,1,0,0,
       0,0,1,0,0,0,
       0,0,0,0,0,0,
      };
    std::vector<int> gliderStepped2
      {0,0,0,0,0,0,
       0,0,0,0,0,0,
       0,0,0,1,0,0,
       0,1,0,1,0,0,
       0,0,1,1,0,0,
       0,0,0,0,0,0,
      };
    std::vector<int> newglider
      {0,0,0,0,0,0,
       0,0,0,0,0,0,
       0,0,1,0,0,0,
       0,0,0,1,1,0,
       0,0,1,1,0,0,
       0,0,0,0,0,0,
      };
    board.set_state(glider);
    board.next_board_state();
    CHECK( board.get_board() == gliderStepped );
    board.next_board_state();
    CHECK( board.get_board() == gliderStepped2 );
    board.next_board_state();
    CHECK( board.get_board() == newglider );
  };
}
TEST_CASE( "Test that the next_board_state correctly steps to new state for 5x7 board",
	   "[GameBoard]" ) {
  GameBoard board{5, 7};
  std::vector<int> emptyBoard(5*7, 0);
  std::vector<int> oneCenteredCellBoard
    {0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,1,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
    };
  std::vector<int> oneCornerCellBoard
    {0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,1,
    };
  std::vector<int> twoCornerCellBoard
    {0,0,0,0,1,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,1,
    };
  std::vector<int> fourCellClusterBoard
    {0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,1,1,
     0,0,0,1,1,
    };
  std::vector<int> fourCellClusterBoard2
    {0,0,0,1,1,
     0,0,0,1,1,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
    };
  std::vector<int> diagonalBoard
    {1,0,0,0,0,
     0,1,0,0,0,
     0,0,1,0,0,
     0,0,0,1,0,
     0,0,0,0,1,
     0,0,0,0,0,
     0,0,0,0,0,
    };
  std::vector<int> diagonalBoardStepped
    {0,0,0,0,0,
     0,1,0,0,0,
     0,0,1,0,0,
     0,0,0,1,0,
     0,0,0,0,0,
     0,0,0,0,0,
     0,0,0,0,0,
    };

  SECTION( "live cells with less than 2 neighbours die. Dead cells stay dead") {
    board.set_state(oneCenteredCellBoard);
    board.next_board_state();
    CHECK( board.get_board() == emptyBoard);

    board.set_state(oneCornerCellBoard);
    board.next_board_state();
    CHECK( board.get_board() == emptyBoard);

    board.set_state(twoCornerCellBoard);
    board.next_board_state();
    CHECK( board.get_board() == emptyBoard);

    board.set_state(diagonalBoard);
    board.next_board_state();
    CHECK( board.get_board() == diagonalBoardStepped);

  }

  SECTION( "Any live cell with 2 or 3 live neighbours stays alive" ) {
    board.set_state(fourCellClusterBoard);
    board.next_board_state();
    CHECK( board.get_board() == fourCellClusterBoard);
    board.set_state(fourCellClusterBoard2);
    board.next_board_state();
    CHECK( board.get_board() == fourCellClusterBoard2);
  }
}



TEST_CASE( "Test that the next_board_state correctly steps to new state for 3x3 board",
	   "[GameBoard]" ) {
  GameBoard board{3, 3};
  std::vector<int> emptyBoard(3*3, 0);
  std::vector<int> oneCenteredCellBoard
    {0,0,0,0,1,0,0,0,0};
  std::vector<int> oneCornerCellBoard
    {0,0,0,0,0,0,0,0,1};
  std::vector<int> twoCornerCellBoard
    {1,0,0,0,0,0,0,0,1};
  std::vector<int> diagonalBoard
    {1,0,0,0,1,0,0,0,1};
  std::vector<int> fourCellClusterBoard
    {0,0,0,0,1,1,0,1,1};
  std::vector<int> fourCellClusterBoard2
    {0,1,1,0,1,1,0,0,0};

  SECTION( "live cells with less than 2 neighbours die. Dead cells stay dead") {
    board.set_state(oneCenteredCellBoard);
    board.next_board_state();
    CHECK( board.get_board() == emptyBoard);

    board.set_state(oneCornerCellBoard);
    board.next_board_state();
    CHECK( board.get_board() == emptyBoard);

    board.set_state(twoCornerCellBoard);
    board.next_board_state();
    CHECK( board.get_board() == emptyBoard);
  }

  SECTION( "Any live cell with 2 or 3 live neighbours stays alive" ) {
    board.set_state(diagonalBoard);
    board.next_board_state();
    CHECK( board.get_board() == oneCenteredCellBoard);

    board.set_state(fourCellClusterBoard);
    board.next_board_state();
    CHECK( board.get_board() == fourCellClusterBoard);
    board.set_state(fourCellClusterBoard2);
    board.next_board_state();
    CHECK( board.get_board() == fourCellClusterBoard2);
  }
}

TEST_CASE( "Test that set_state sets new state",
	   "[GameBoard]" ) {
  GameBoard board{3, 3};
  std::vector<int> emptyBoard
    {0,0,0,0,0,0,0,0,0};
  std::vector<int> oneCenteredCellBoard
    {0,0,0,0,1,0,0,0,0};

  board.set_state(oneCenteredCellBoard);

  SECTION( "setting state of board changes the board") {
    std::vector<int> tauBoard{1,1,1,1,1,1,1,1,1};
    board.set_state(tauBoard);
    CHECK( board.get_board() == tauBoard );
  }

  SECTION( "setting state of board incorrectly doesn't change the board") {
    std::vector<int> faultyOneCenteredCellBoard{0,0,0,0,0,1,0,0,0,0};
    board.set_state(faultyOneCenteredCellBoard);
    CHECK( board.get_board() == oneCenteredCellBoard );
    CHECK( board.get_board() != faultyOneCenteredCellBoard );
  }
}
