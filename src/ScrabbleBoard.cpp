#include "ScrabbleBoard.h"
#include <iostream>
#include <stdexcept>

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

bool ScrabbleBoard::setBoardState(BoardState bs)
{
	BoardState oldState = boardState;
	boardState = bs;
	bool isValid = boardIsValid();
	if(isValid) return true;
	boardState = oldState;
	return false;
}

std::string ScrabbleBoard::toString(bool showMultipliers) const
{
	// First allocate a string with enough room to hold the entire board. This
	// needs to be length*width + length, (for the new line at the end of each
	// row).
	size_t stringLength = boardState.letterVector.size() *
		boardState.letterVector[0].size() + boardState.letterVector.size();
	std::string returnString(stringLength, '.');

	// Make it so there is a new line after each row.
	for(size_t i = boardState.letterVector[0].size();
		i < stringLength;
		i += boardState.letterVector[0].size() + 1)
	{
		returnString[i] = '\n';
	}


	// Copy the board letters into the string.
	for(size_t i = 0; i < boardState.letterVector.size(); i++)
	{
		for(size_t j = 0; j < boardState.letterVector[0].size(); j++)
		{
			returnString[i * (boardState.letterVector[0].size() + 1) + j] =
				boardState.letterVector[i][j];
		}
	}

	// If the function is set to show the multipliers, add those. Ovewrite any
	// existing letters on the same spot.
	if(showMultipliers)
	{
		for(size_t i = 0; i < boardState.letterVector.size(); i++)
		{
			for(size_t j = 0; j < boardState.letterVector[0].size(); j++)
			{
				if(boardState.wordMultipliers[i][j] != 1)
				{
					returnString[i * (boardState.letterVector[0].size() + 1) + j] =
						boardState.wordMultipliers[i][j] + 48;
				}
				else if(boardState.letterMultipliers[i][j] != 1)
				{
					returnString[i * (boardState.letterVector[0].size() + 1) + j] =
						boardState.letterMultipliers[i][j] + 48;
				}
			}
		}
	}

	return returnString;
}

void ScrabbleBoard::printBoard(bool showMultipliers) const
{
	std::cout << toString(showMultipliers) << std::endl;
}
