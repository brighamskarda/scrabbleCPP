#include "ScrabbleBoard.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <climits>

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

int ScrabbleBoard::putWordFreeplay(size_t x, size_t y, bool vertical,
	std::string s)
{
	// Make a copy of the boardState and blankTileLocation to revert back to in
	// case the word turns out to be invalid.
	BoardState tempState = boardState;
	std::vector<std::pair<size_t, size_t>> tempBlankTileLocation =
		blankTileLocation;

	// If the word is not in the dictionary it is invalid. Remove whitespace
	// first.
	std::string tempString = s;
	for(size_t i = tempString.size(); i > 0; i--)
	{
		if(tempString[i-1] == ' ') tempString.erase(i-1, 1);
	}
	if(dictionary.count(tempString) <= 0) return INT_MIN;

	// If the word goes off the board it is invalid.
	if(x >= boardState.letterVector[0].size() ||
		y >= boardState.letterVector.size() ||
		(vertical && y + s.size() > boardState.letterVector.size()) ||
		(!vertical && x + s.size() > boardState.letterVector[0].size())
	) return INT_MIN;

	// Start putting in letters.
	size_t tilesPlaced = 0;
	size_t stringPosition = 0;
	int totalScore = 0;
	int baseWordScore = 0;
	int baseWordMultiplier = 1;
	size_t currentX = x;
	size_t currentY = y;
	bool goBack = false;
	for( ; stringPosition < s.size(); stringPosition++)
	{
		// If the spot is empty
		if(boardState.letterVector[currentY][currentX] == '.')
		{
			if(s[stringPosition] != ' ')
			{
				boardState.letterVector[currentY][currentX] = s[stringPosition];
			}
			// If you use a blank tile.
			else
			{
				boardState.letterVector[currentY][currentX] =
					s[stringPosition+1];
				blankTileLocation.push_back({currentX, currentY});
			}
			tilesPlaced++;
			// If the player has placed more than 7 tiles, then the move
			// become invalid.
			if(tilesPlaced > 7)
			{
				goBack = true;
				break;
			}
			// Calculate scores, and remove the letter from the bag.
			if(boardState.letterBag.at(s[stringPosition]) > 0)
			{
				boardState.letterBag.at(s[stringPosition])--;
				baseWordScore += boardState.letterPoints.at(s[stringPosition]) *
					boardState.letterMultipliers[currentY][currentX];
				baseWordMultiplier *=
					boardState.wordMultipliers[currentY][currentX];
				int additionalWordScore = calcAdditionalWord(currentX, currentY,
					vertical);
				if(additionalWordScore == INT_MIN)
				{
					goBack = true;
					break;
				}
				totalScore += additionalWordScore;
			}
			// There is no tile available
			else
			{
				goBack = true;
				break;
			}
		}
		// If the spot already has the correct letter in place. Be sure to still
		// add that letter to the baseWordScore. (only if its not a blank)
		else if(boardState.letterVector[currentY][currentX] ==
			s[stringPosition] && !checkForBlankTile(currentX, currentY))
		{
			baseWordScore += boardState.letterPoints.at(s[stringPosition]);
		}
		// If the spot is already taken by an incorrect letter then the move is
		// invalid.
		else if(boardState.letterVector[currentY][currentX] !=
			s[stringPosition])
		{
			goBack = true;
			break;
		}
		// Increment in the correct direction.
		if(vertical) currentY++;
		else currentX++;
		// If the letter was a space, we need to increment again.
		if(s[stringPosition] == ' ') stringPosition++;
	}
	// Revert to the previous state if the word turns out to be an invalid play.
	if(goBack)
	{
		boardState = tempState;
		blankTileLocation = tempBlankTileLocation;
		return INT_MIN;
	}
	totalScore += baseWordScore * baseWordMultiplier;

	// Add 50 points if the player placed all 7 of their tiles.
	if(tilesPlaced == 7) totalScore += 50;


	return totalScore;
}

void ScrabbleBoard::loadDictionary()
{
	std::ifstream dic("resources/CollinsScrabbleWords2019.txt");
	std::string currentWord;
	std::getline(dic, currentWord);
	while(true)
	{
		dictionary.insert(currentWord);
		if(dic.eof()) break;
		std::getline(dic, currentWord);
	}
	std::cout << "Finished loading dictionary" << std::endl;
}

int ScrabbleBoard::calcAdditionalWord(size_t x, size_t y, bool vertical) const
{
	int wordScore = 0;
	std::string newWord;
	size_t wordLength = 0;
	// If vertical, then we need to search for a new word horizontally.
	if(vertical)
	{
		// Search left
		size_t startingX = x;
		while(startingX > 0 && boardState.letterVector[y][startingX-1] != '.')
		{
			startingX--;
			wordLength++;
		}
		// Search right
		size_t endingX = x;
		while(endingX < boardState.letterVector[y].size()-1 &&
			boardState.letterVector[y][endingX+1] != '.')
		{
			endingX++;
			wordLength++;
		}
		// Check if there is actually a word to be found.
		if(wordLength == 0) return 0;
		wordLength++;
		// Form the string and generate a score for it.
		newWord.reserve(wordLength);
		for(size_t xOffset = 0; xOffset < wordLength; xOffset++)
		{
			newWord.push_back(boardState.letterVector[y][startingX + xOffset]);
			// Add that letter to the score. Make sure to add on the
			// letterMultiplier only if its the letter you placed down.
			if(startingX + xOffset == x)
			{
				if(!checkForBlankTile(startingX + xOffset, y))
				{
					wordScore += boardState.letterPoints.at(
						boardState.letterVector[y][startingX + xOffset]) *
						boardState.letterMultipliers[y][x];
				}
			}
			else
			{
				if(!checkForBlankTile(startingX + xOffset, y))
				{
					wordScore += boardState.letterPoints.at(
						boardState.letterVector[y][startingX + xOffset]);
				}
			}
		}

		// Check if the newWord is in the dictionary.
		if(dictionary.count(newWord) < 1) return INT_MIN;
		return wordScore * boardState.wordMultipliers[y][x];
	}
	// If horizontal, then we need to search for a new word vertically.
	else
	{
		// Search up
		size_t startingY = y;
		while(startingY > 0 && boardState.letterVector[startingY-1][x] != '.')
		{
			startingY--;
			wordLength++;
		}
		// Search down
		size_t endingY = y;
		while(endingY < boardState.letterVector.size()-1 &&
			boardState.letterVector[endingY+1][x] != '.')
		{
			endingY++;
			wordLength++;
		}
		// Check if there is actually a word to be found.
		if(wordLength == 0) return 0;
		wordLength++;
		// Form the string and generate a score for it.
		newWord.reserve(wordLength);
		for(size_t yOffset = 0; yOffset < wordLength; yOffset++)
		{
			newWord.push_back(boardState.letterVector[startingY + yOffset][x]);
			// Add that letter to the score. Make sure to add on the
			// letterMultiplier only if its the letter you placed down.
			if(startingY + yOffset == y)
			{
				if(!checkForBlankTile(x, startingY + yOffset))
				{
					wordScore += boardState.letterPoints.at(
						boardState.letterVector[startingY +yOffset][x]) *
						boardState.letterMultipliers[y][x];
				}
			}
			else
			{
				if(!checkForBlankTile(x, startingY + yOffset))
				{
					wordScore += boardState.letterPoints.at(
						boardState.letterVector[startingY+yOffset][x]);
				}
			}
		}

		// Check if the newWord is in the dictionary.
		if(dictionary.count(newWord) < 1) return INT_MIN;
		return wordScore * boardState.wordMultipliers[y][x];
	}
}

bool ScrabbleBoard::checkForBlankTile(size_t x, size_t y) const
{
	for(std::pair<size_t, size_t> p : blankTileLocation)
	{
		if(p.first == x && p.second == y) return true;
	}
	return false;
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
	loadDictionary();
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

int ScrabbleBoard::putWord(size_t x, size_t y, bool vertical, std::string s)
{
	// Go to freeplay mode if enabled.
	if(freePlay) return putWordFreeplay(x, y, vertical, s);

	// Make a copy of the boardState and blankTileLocation to revert back to in
	// case the word turns out to be invalid.
	BoardState tempState = boardState;
	std::vector<std::pair<size_t, size_t>> tempBlankTileLocation =
		blankTileLocation;

	// If the word is not in the dictionary it is invalid. (Remove whitespace
	// first.)
	std::string tempString = s;
	for(size_t i = tempString.size(); i > 0; i--)
	{
		if(tempString[i-1] == ' ') tempString.erase(i-1, 1);
	}
	if(dictionary.count(tempString) <= 0) return INT_MIN;

	// If the word goes off the board it is invalid.
	if(x >= boardState.letterVector[0].size() ||
		y >= boardState.letterVector.size() ||
		(vertical && y + s.size() > boardState.letterVector.size()) ||
		(!vertical && x + s.size() > boardState.letterVector[0].size())
	) return INT_MIN;

	// Start putting in letters.
	size_t tilesPlaced = 0;
	size_t stringPosition = 0;
	int totalScore = 0;
	int baseWordScore = 0;
	int baseWordMultiplier = 1;
	size_t currentX = x;
	size_t currentY = y;
	bool goBack = false;
	bool additionalWordCreated = false;
	for( ; stringPosition < s.size(); stringPosition++)
	{
		// If the spot is empty
		if(boardState.letterVector[currentY][currentX] == '.')
		{
			if(s[stringPosition] != ' ')
			{
				boardState.letterVector[currentY][currentX] = s[stringPosition];
			}
			// If you use a blank tile.
			else
			{
				boardState.letterVector[currentY][currentX] =
					s[stringPosition+1];
				blankTileLocation.push_back({currentX, currentY});
			}
			tilesPlaced++;
			// If the player has placed more than 7 tiles, then the move
			// become invalid.
			if(tilesPlaced > 7)
			{
				goBack = true;
				break;
			}
			// Calculate scores, and remove the letter from the bag.
			if(boardState.letterBag.at(s[stringPosition]) > 0)
			{
				boardState.letterBag.at(s[stringPosition])--;
				baseWordScore += boardState.letterPoints.at(s[stringPosition]) *
					boardState.letterMultipliers[currentY][currentX];
				baseWordMultiplier *=
					boardState.wordMultipliers[currentY][currentX];
				int additionalWordScore = calcAdditionalWord(currentX, currentY,
					vertical);
				if(additionalWordScore == INT_MIN)
				{
					goBack = true;
					break;
				}
				totalScore += additionalWordScore;
				if(additionalWordScore > 0) additionalWordCreated = true;
			}
			// There is no tile available
			else
			{
				goBack = true;
				break;
			}
		}
		// If the spot already has the correct letter in place. Be sure to still
		// add that letter to the baseWordScore. (only if its not a blank)
		else if(boardState.letterVector[currentY][currentX] ==
			s[stringPosition] && !checkForBlankTile(currentX, currentY))
		{
			baseWordScore += boardState.letterPoints.at(s[stringPosition]);
		}
		// If the spot is already taken by an incorrect letter then the move is
		// invalid.
		else if(boardState.letterVector[currentY][currentX] !=
			s[stringPosition])
		{
			goBack = true;
			break;
		}
		// Increment in the correct direction.
		if(vertical) currentY++;
		else currentX++;
		// If the letter was a space, we need to increment again.
		if(s[stringPosition] == ' ') stringPosition++;
	}
	// If the center tile is not filled in, then the move is invalid.
	if(boardState.letterVector[7][7] == '.') goBack = true;

	// If the word does not connect to the rest, then the move is invalid.
	if(tempState.letterVector[7][7] != '.' && !additionalWordCreated &&
		tilesPlaced == tempString.size()) goBack = true;

	// Revert to the previous state if the word turns out to be an invalid play.
	if(goBack)
	{
		boardState = tempState;
		blankTileLocation = tempBlankTileLocation;
		return INT_MIN;
	}
	totalScore += baseWordScore * baseWordMultiplier;

	// Add 50 points if the player placed all 7 of their tiles.
	if(tilesPlaced == 7) totalScore += 50;


	return totalScore;
}
