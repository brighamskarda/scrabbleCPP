#ifndef SCRABBLE_BOARD_H
#define SCRABBLE_BOARD_H
#include "BoardState.h"


class ScrabbleBoard
{
private:
	BoardState boardState;
	bool freePlay;

	/**
		@return if the currently stored boardState is valid then return true,
			otherwise return false. Checks that all of the vectors are a square
			of the same size.
	*/
	bool boardIsValid() const;
public:
	/**
		Takes in a boardState and verifies that it is valid. Mostly if the
		vectors in the board state are of different sizes, then an exception
		will be thrown.

		Freeplay mode is default false, but can be set to true if you don't want
		to worry about the normal rules of scrabble and you just want to add
		words to the board without thinking.
	*/
	ScrabbleBoard(BoardState bs, bool fp = false);
};


#endif