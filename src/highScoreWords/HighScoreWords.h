#ifndef HIGH_SCORE_WORDS_H
#define HIGH_SCORE_WORDS_H
#include "../ScrabbleBoard.h"
#include <vector>
#include <string>
#include <utility>

class HighScoreWords
{
private:
	ScrabbleBoard sb;
	std::vector<std::string> dictionary = {};
	std::vector<std::pair<std::string, int>> baseWords = {};


	void loadDictionary();

	/**
		@param num The best *num* words are saved.
	*/
	void loadBaseWords(size_t num = 20);

	void printBaseWords();

public:
	HighScoreWords();

};
#endif