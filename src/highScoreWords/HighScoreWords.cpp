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

void HighScoreWords::printBaseWords()
{
	for(std::pair<std::string, int> p : baseWords)
	{
		std::cout << p.first << " - " << p.second << '\n';
	}
	std::cout << std::flush;
}

void HighScoreWords::loadBaseWords(size_t num)
{
	for(std::string word : dictionary)
	{
		sb.refreshBoard();
		int score = sb.putWord(0, 0, true, word);
		if(baseWords.size() < num)
		{
			baseWords.push_back({word, score});
		}
		else
		{
			for(size_t i = 0; i < baseWords.size(); i++)
			{
				if(baseWords[i].second < score)
				{
					baseWords[i] = {word, score};
					break;
				}
			}
		}

	}
}

HighScoreWords::HighScoreWords()
{
	sb.setFreePlay(true);
	loadDictionary();
	loadBaseWords();
	printBaseWords();
}