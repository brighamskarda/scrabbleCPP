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
	std::vector<std::string> baseWords = {};


	void loadDictionary();

	/**
		@param num The best *num* words are saved.
	*/
	void loadBaseWords(int num);

public:
	HighScoreWords();

};
#endif