#include <iostream>
#include <map>
#include <vector>
#include "BoardState.h"
#include "ScrabbleBoard.h"

int main() {
	std::cout << "Hello World" << std::endl;

	std::map<char, short> myMap = {{'a', 1}, {'b', 2}, {'c', 3}};
	std::vector<std::vector<char>> lv = {
											{'.', '.', '.'},
											{'.', '.', '.'},
											{'.', '.', '.'}
										};

	std::vector<std::vector<char>> wm = {
											{'1', '1', '1'},
											{'1', '1', '1'},
											{'1', '1', '1'}
										};
	std::vector<std::vector<char>> lm = {
											{'2', '2', '2'},
											{'2', '2', '2'},
											{'2', '2', '2'}
										};
	BoardState bs(myMap, lv, wm, lm);
	ScrabbleBoard sb(bs);

	return 0;
}