#include "BoardState.h"

int BoardState::tilesLeftInBag()
{
	int total = 0;
	for(std::map<char, short>::iterator it = letterBag.begin();
		it != letterBag.end(); it++)
	{
		total += it->second;
	}
	return total;
}