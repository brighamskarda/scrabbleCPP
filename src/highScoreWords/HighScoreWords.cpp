#include "HighScoreWords.h"
#include "../constants.h"
#include <fstream>
#include <iostream>

void HighScoreWords::loadDictionary()
{
	std::ifstream dic(std::string(constants::DICTIONARY));
	std::string currentWord;
	std::getline(dic, currentWord);
	while(true)
	{
		dictionary.push_back(currentWord);
		if(dic.eof()) break;
		std::getline(dic, currentWord);
	}
	std::cout << "Finished loading dictionary for HighScoreWords" << std::endl;
}

void HighScoreWords::loadBaseWords(int num)
{

}

HighScoreWords::HighScoreWords()
{
	loadDictionary();

}