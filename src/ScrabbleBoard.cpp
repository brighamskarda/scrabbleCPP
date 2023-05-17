#include "ScrabbleBoard.h"
#include <stdexcept>

ScrabbleBoard::ScrabbleBoard(BoardState bs, bool fp) : boardState(bs),
	freePlay(fp)
{
	if(boardIsValid() == false)
	{
		throw std::invalid_argument("letterVector, wordMultipliers, and "
		"letterMultipliers vectors are not all of the same size, or have a "
		"length of 0");
	}
}

bool ScrabbleBoard::boardIsValid() const
{
	// Get the length and width of the letterVector. Return false if 0
	size_t length = boardState.letterVector.size();
	if(length == 0) return false;
	size_t width = boardState.letterVector[0].size();
	if(width == 0) return false;

	// Make sure that all rows in the letterVector are of the first rows width.
	for(std::vector<char> row : boardState.letterVector)
	{
		if(row.size() != width) return false;
	}

	// Make sure the length, and width of each row in the wordMultipliers vector
	// match the letterVector length and width.
	if(boardState.wordMultipliers.size() != length) return false;

	for(std::vector<char> row : boardState.wordMultipliers)
	{
		if(row.size() != width) return false;
	}

	// Make sure the length, and width of each row in the letterMultipliers
	// vector match the letterVector length and width.
	if(boardState.letterMultipliers.size() != length) return false;

	for(std::vector<char> row : boardState.letterMultipliers)
	{
		if(row.size() != width) return false;
	}

	// If you make it hear that means the boardState should be valid, at least
	// in terms of vector dimensions.
	return true;
}