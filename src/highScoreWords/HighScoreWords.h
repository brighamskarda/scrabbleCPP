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
	std::map<char, std::vector<std::string>> alphabeticalDic = {};
	// This map is very special. It includes only words that are still valid
	// words while still having their first letter cut off.
	std::map<char, std::vector<std::string>> specAlphDic = {};
	std::vector<std::pair<std::string, int>> baseWords = {};


	/**
	 * Loads the master dictionary, but also loads an alphabetical dictionary.
	 */
	void loadDictionaries();

	/**
		@param num The best *num* words are saved.
	*/
	void loadBaseWords(size_t num = 100);

	void printBaseWords();

public:
	HighScoreWords();
	void start();

};
#endif