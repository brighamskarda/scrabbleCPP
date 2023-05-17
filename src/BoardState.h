#ifndef BOARD_STATE_H
#define BOARD_STATE_H
#include <map>
#include <vector>

struct BoardState
{
public:
	std::map<char, short> letterBag;
	std::vector<std::vector<char>> letterVector;
	const std::vector<std::vector<char>> wordMultipliers;
	const std::vector<std::vector<char>> letterMultipliers;
	/**
		Takes in all of the paremeters necessary to start a game of scrabble.
		It is also possible to give it a game that is already in progress.
		As of now, it only supports ASCII characters, perhaps someday it can
		be internationalized.
		@param lb Pointer to a map of char - number of that character
			space represents a blank tile.
		@param lv A 2D vector representing places on the board that
			can hold letters. '.' represents an empty spot.
		@param wm A 2D vector representing places on the board that
			multiply a word's score. Default 1 for normal, 2 for 2x, etc.
			Supports negative multipliers. Must have same dimensions as lv.
		@param lm A 2D vector representing places on the board that
			multiply a letter's score. Default 1 for normal, 2 for 2x, etc.
			Supports negative multipliers. Must have same dimensions as lv.
	*/
	BoardState(std::map<char, short> lb,
		std::vector<std::vector<char>> lv,
		const std::vector<std::vector<char>> wm,
		const std::vector<std::vector<char>> lm) : letterBag(lb),
		letterVector(lv), wordMultipliers(wm), letterMultipliers(lm) {}
};



#endif