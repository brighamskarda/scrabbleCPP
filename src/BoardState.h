#ifndef BOARD_STATE_H
#define BOARD_STATE_H
#include <map>
#include <vector>
#include <utility>
#include <climits>

struct BoardState
{
public:
	std::map<char, short> letterBag;
	std::map<char, short> letterPoints;
	std::vector<std::vector<char>> letterVector;
	std::vector<std::vector<char>> wordMultipliers;
	std::vector<std::vector<char>> letterMultipliers;
	std::vector<std::pair<size_t, size_t>> blankTileLocation = {};
	/**
		Takes in all of the paremeters necessary to start a game of scrabble.
		It is also possible to give it a game that is already in progress.
		As of now, it only supports ASCII characters, perhaps someday it can
		be internationalized.
		@param lb A map of char - number of that character
			space represents a blank tile.
		@param lp A map of char - value of that character
			space represents a blank tile.
		@param lv A 2D vector representing places on the board that
			can hold letters. '.' represents an empty spot.
		@param wm A 2D vector representing places on the board that
			multiply a word's score. Default 1 for normal, 2 for 2x, etc.
			Supports negative multipliers. Must have same dimensions as lv.
		@param lm A 2D vector representing places on the board that
			multiply a letter's score. Default 1 for normal, 2 for 2x, etc.
			Supports negative multipliers. Must have same dimensions as lv.
		@param btl A vector of pairs (x, y) representing where the blankTiles
			are located on the scrabbleBoard.
	*/
	BoardState(std::map<char, short> lb = {},
		std::map<char, short> lp = {},
		std::vector<std::vector<char>> lv = {},
		std::vector<std::vector<char>> wm = {},
		std::vector<std::vector<char>> lm = {},
		std::vector<std::pair<size_t, size_t>> btl = {}) : letterBag(lb), letterPoints(lp),
		letterVector(lv), wordMultipliers(wm), letterMultipliers(lm),
		blankTileLocation(btl) {}

	int tilesLeftInBag();
};



#endif