#ifndef RANDOM_GAMES_H
#define RANDOM_GAMES_H
#include "ScrabbleBoard.h"
#include <random>
#include <ctime>

class RandomGames
{
private:
	ScrabbleBoard sb;
	std::vector<std::string> dictionary = {};
	BoardState freshBoard;
	BoardState bestBoardState;
	std::vector<std::pair<std::string, int>> bestWordsPlayed;
	int bestPlayScore = 0;
	unsigned long long int gamesPlayed = 1;
	std::mt19937 random;
	time_t startTime = 0;


	/**
		Loads a fresh boardState into our scrabbleBoard object.
	*/
	void refreshBoard();

	void loadDictionary();

	std::string selectRandomWord();

	void printGameInfo();

public:
	/**
		Initializes the internal scrabbleBoard object with the standard scrabble
		board and bag. Also loads the dictionary.
	*/
	RandomGames();
	/**
		Runs random, but still valid games of scrabble forever. Every time a new
		best move is found, it is printed to the console as follows.
		1. The order of words played.
		2. The final board.
	*/
	void runRandomGames();
};

#endif