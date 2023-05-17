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
	std::cout << bs.letterVector[0][2] << std::endl;


	return 0;
}