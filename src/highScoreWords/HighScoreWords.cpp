#include "HighScoreWords.h"
#include "../constants.h"
#include <fstream>
#include <iostream>
#include <random>

void HighScoreWords::loadDictionaries()
{
	// Initialize the alphabeticalDic map()
	for(char i = 'A'; i <= 'Z'; i++)
	{
		alphabeticalDic.insert({i, {}});
		specAlphDic.insert({i, {}});
	}
	std::ifstream dic((std::string(constants::DICTIONARY)));
	std::string currentWord;
	std::getline(dic, currentWord);
	while(true)
	{
		dictionary.push_back(currentWord);
		alphabeticalDic[currentWord[0]].push_back(currentWord);
		if(dic.eof()) break;
		std::getline(dic, currentWord);
	}
	// Add words to the specAlphDic if they can exist in the dictionary
	// without their first letter.
	for(std::string w : dictionary)
	{
		std::string trimmedWord = w.substr(1);
		bool isInDic = false;
		for(std::string w2 : alphabeticalDic[trimmedWord[0]])
		{
			if(trimmedWord == w2)
			{
				isInDic = true;
				break;
			}
		}
		if(isInDic)
		{
			specAlphDic[w[0]].push_back(w);
		}
	}

	std::cout << "Finished loading dictionaries for HighScoreWords" << std::endl;
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
		if(word.length() != 15) continue;
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
	loadDictionaries();
	loadBaseWords();
	printBaseWords();
}

void HighScoreWords::start()
{
	int highScore = 0;
	BoardState bestBoardState = sb.getBoardState();
	std::mt19937 random;
	random = std::mt19937(time(NULL));
	while(true)
	{
		// refresh the board
		sb.refreshBoard();
		// Select a random base word
		std::string baseWord = baseWords[random() % baseWords.size()].first;
		sb.putWord(0, 0, true, baseWord);
		// Make the data structure for the extra words. the first part of the
		// pair is the index, the second part is the word.
		std::vector<std::pair<char, std::string>> extraWords = {};
		// Get the three triple words.
		bool wordPlaced = false;
		while(!wordPlaced)
		{
			extraWords.push_back({0, specAlphDic[baseWord[0]][random() %
				specAlphDic[baseWord[0]].size()]});
			if(sb.putWord(1, 0, false, extraWords[0].second.substr(1)) !=
				INT_MIN)
			{
				wordPlaced = true;
			}
			else extraWords.pop_back();
		}
		wordPlaced = false;
		while(!wordPlaced)
		{
			extraWords.push_back({7, specAlphDic[baseWord[7]][random() %
				specAlphDic[baseWord[7]].size()]});
			if(sb.putWord(1, 7, false, extraWords[1].second.substr(1)) !=
				INT_MIN)
			{
				wordPlaced = true;
			}
			else extraWords.pop_back();
		}
		wordPlaced = false;
		while(!wordPlaced)
		{
			extraWords.push_back({14, specAlphDic[baseWord[14]][random() %
																specAlphDic[baseWord[14]].size()]});
			if(sb.putWord(1, 14, false, extraWords[2].second.substr(1)) !=
				INT_MIN)
			{
				wordPlaced = true;
			}
			else extraWords.pop_back();
		}

		/*// Get the other five words
		for(int i = 2; i < 7;)
		{
			*//*
			 * TODO Get the five extra words. Also set it up in a way that
			 * it checks that the words create valid vertical functions as well.
			 * Since specAlphDic is so much smaller than the full dictionary
			 * it is probably okay to loop through every possible word to see
			 * it is is valid.
			 *//*
			char index = 0;
			bool newIndex = false;
			while(!newIndex)
			{
				index = random() % 15;
				newIndex = true;
				for(std::pair<char, std::string> p : extraWords)
				{
					if(p.first == index)
					{
						newIndex = false;
						break;
					}
				}
			}
			size_t startIndex = random() % specAlphDic[baseWord[index]].size();
			size_t numIterations = 0;
			while(numIterations < specAlphDic[baseWord[index]].size())
			{
				int points = sb.putWord(0, index, false,
					specAlphDic[baseWord[index]][startIndex]);
				if(points != INT_MIN)
				{
					extraWords.push_back({index,
						specAlphDic[baseWord[index]][startIndex]});
					i++;
					break;
				}
				numIterations++;
				startIndex++;
				if(startIndex >= specAlphDic[baseWord[index]].size())
				{
					startIndex = 0;
				}
			}
		}*/

		// Place down the base word and print out the number of points it gets.
		sb.refreshBoard();
		for(std::pair<char, std::string> p : extraWords)
		{
			sb.putWord(1, p.first, false, p.second.substr(1));
		}
		int finalWordPoints = sb.putWord(0, 0, true, baseWord);
		if(finalWordPoints > highScore)
		{
			bestBoardState = sb.getBoardState();
			highScore = finalWordPoints;
			std::cout << "Points generated - " << finalWordPoints << '\n';
			sb.printBoard();
		}
	}
}