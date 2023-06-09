#include "RandomGames.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <climits>
#include <ctime>

void RandomGames::refreshBoard()
{
	sb.setBoardState(freshBoard);
}

void RandomGames::loadDictionary()
{
	std::ifstream dic((std::string(constants::DICTIONARY)));
	std::string currentWord;
	std::getline(dic, currentWord);
	while(true)
	{
		dictionary.push_back(currentWord);
		if(dic.eof()) break;
		std::getline(dic, currentWord);
	}
	std::cout << "Finished loading dictionary for RandomGames" << std::endl;
}

std::string RandomGames::selectRandomWord()
{
	int randomIndex = random() % dictionary.size();
	std::string w = dictionary[randomIndex];
	for(size_t i = 0; i < w.size(); i++)
	{
		if(random() % 50 == 0) w.insert(i, 1, ' ');
	}
	return w;
}

void RandomGames::printGameInfo()
{
	time_t currentTime = time(NULL);
	time_t time_elapsed = currentTime - startTime;
	std::cout << "Time: " << ctime(&currentTime);
	std::cout << "Time Elapsed: " << time_elapsed / 3600 << ":" <<
		(time_elapsed / 60) % 60 << ":" << time_elapsed % 60 << "\n";
	std::cout << "Games Played: " << gamesPlayed << "\n";
	std::cout << "Average Games Per Minute: " <<
		(double)gamesPlayed / (double)(time_elapsed / 60) << "\n";
	for(size_t i = 0; i < bestWordsPlayed.size(); i++)
	{
		std::cout << bestWordsPlayed[i].first << " - " <<
			bestWordsPlayed[i].second << "\n";
	}
	std::cout << sb.toString() << "\n";

	std::cout << std::endl;
}

RandomGames::RandomGames()
{
	loadDictionary();
	freshBoard = sb.getBoardState();
	random = std::mt19937(time(NULL));
}

void RandomGames::runRandomGames()
{
	std::vector<std::pair<std::string, int>> wordsPlayed;
	BoardState currentBoardState;
	startTime = time(NULL);
	std::cout << "Start time: " << ctime(&startTime) << std::endl;

	// Forever Loop
	while(true)
	{
		// Each Individual game;
		refreshBoard();
		currentBoardState = sb.getBoardState();
		wordsPlayed.clear();
		unsigned short numberOfBadWordsBeforeThis = 0;
		while( currentBoardState.tilesLeftInBag() > 6 &&
			numberOfBadWordsBeforeThis < 100)
		{
			std::string word = selectRandomWord();
			bool wordPlaced = false;
			for(size_t i = 0; i < 15; i++)
			{
				for(size_t j = 0; j < 15; j++)
				{
					int score = sb.putWord(i, j, false, word);
					if(score != INT_MIN)
					{
						currentBoardState = sb.getBoardState();
						wordsPlayed.push_back({word, score});
						if(score > bestPlayScore)
						{
							bestPlayScore = score;
							bestBoardState = currentBoardState;
							bestWordsPlayed = wordsPlayed;
							printGameInfo();
						}
						wordPlaced = true;
						break;
					}
					score = sb.putWord(i, j, true, word);
					if(score != INT_MIN)
					{
						currentBoardState = sb.getBoardState();
						wordsPlayed.push_back({word, score});
						if(score > bestPlayScore)
						{
							bestPlayScore = score;
							bestBoardState = currentBoardState;
							bestWordsPlayed = wordsPlayed;
							printGameInfo();
						}
						wordPlaced = true;
						break;
					}
				}
				if(wordPlaced)
				{
					numberOfBadWordsBeforeThis = 0;
					break;
				}
			}
			if(!wordPlaced) numberOfBadWordsBeforeThis++;
		}
		gamesPlayed++;
	}
}
