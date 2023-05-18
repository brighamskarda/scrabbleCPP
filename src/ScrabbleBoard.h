#ifndef SCRABBLE_BOARD_H
#define SCRABBLE_BOARD_H
#include "BoardState.h"
#include <string>


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
	void setFreePlay(bool fp) { freePlay = fp; }
	bool getFreePlay() const { return freePlay; }
	/**
		Sets the board state, but also veifies if its valid.
		It mostly makes sure that all of the board vectors are of the same
		size and longer than 0. Returns true if valid. Otherwise it does not
		change the boardState.
	*/
	bool setBoardState(BoardState bs);
	BoardState getBoardState() const { return boardState; }
	/**
		Gives a string representing the scrabble baord.
		@param showMultipliers If this is true, then letter and word multipliers
			will be shown. Due to the nature of everything being 1 character
			long, multipliers that aren't 0-9 will now show up correctly.
			They will ovewrite letters that are on their location. Word
			multipliers will overwrite letter multipliers as they are generally
			more valuable.
	*/
	std::string toString(bool showMultipliers = false) const;
	/**
		Same as toString, it just prints it to stdout for you.
	*/
	void printBoard(bool showMultipliers = false) const;

};


#endif