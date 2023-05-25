#include <iostream>
#include <map>
#include <vector>
#include "BoardState.h"
#include "ScrabbleBoard.h"

int main() {
	std::map<char, short> lb = {{'A', 9}, {'B', 2}, {'C', 2}, {'D', 4},
		{'E', 12}, {'F', 2}, {'G', 3}, {'H', 2}, {'I', 9}, {'J', 1}, {'K', 1},
		{'L', 4}, {'M', 2}, {'N', 6}, {'O', 8}, {'P', 2}, {'Q', 1}, {'R', 6},
		{'S', 4}, {'T', 6}, {'U', 4}, {'V', 2}, {'W', 2}, {'X', 1}, {'Y', 2},
		{'Z', 1}, {' ', 2}};
	std::map<char, short> lp = {{'A', 1}, {'B', 3}, {'C', 3}, {'D', 2},
		{'E', 1}, {'F', 4}, {'G', 2}, {'H', 4}, {'I', 1}, {'J', 8}, {'K', 5},
		{'L', 1}, {'M', 3}, {'N', 1}, {'O', 1}, {'P', 3}, {'Q', 10}, {'R', 1},
		{'S', 1}, {'T', 1}, {'U', 1}, {'V', 4}, {'W', 4}, {'X', 8}, {'Y', 4},
		{'Z', 10}, {' ', 0}};
	std::vector<std::vector<char>> lv = {
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}
										};
	std::vector<std::vector<char>> wm = {
								{3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3},
								{1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
								{1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1},
								{1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1},
								{1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{3, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 3},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1},
								{1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1},
								{1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1},
								{1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
								{3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3}
										};
	std::vector<std::vector<char>> lm = {
								{1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1},
								{1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1},
								{2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1},
								{1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1},
								{1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1},
								{1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1},
								{1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1},
								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
								{2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2},
								{1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1},
								{1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1},
								{1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1}
										};
	BoardState bs(lb, lp, lv, wm, lm);
	ScrabbleBoard sb(bs);
	std::cout << "WASHING - " << sb.putWord(5, 7, false, "WASHING")
		<< std::endl;
	std::cout << "RAINWASHING - " << sb.putWord(1, 7, false, "RAINWASHING")
		<< std::endl;
	std::cout << "TWOO NIE - " << sb.putWord(5, 6, true, "TWOO NIE")
		<< std::endl;
	std::cout << "WAKENERS - " << sb.putWord(1, 10, false, "WAKENERS")
		<< std::endl;
	std::cout << "EKE - " << sb.putWord(3, 9, true, "EKE") << std::endl;
	std::cout << "O NETIME - " << sb.putWord(1, 11, false, "O NETIME")
		<< std::endl;
	std::cout << "OOT - " << sb.putWord(0, 12, false, "OOT") << std::endl;
	std::cout << "ON - " << sb.putWord(0, 12, true, "ON") << std::endl;
	std::cout << "REBUT - " << sb.putWord(7, 10, true, "REBUT") << std::endl;
	std::cout << "TING - " << sb.putWord(7, 14, false, "TING") << std::endl;
	std::cout << "JACULATING - " << sb.putWord(1, 14, false, "JACULATING")
		<< std::endl;
	std::cout << "DORM - " << sb.putWord(1, 5, true, "DORM") << std::endl;
	std::cout << "UM - " << sb.putWord(0, 8, false, "UM") << std::endl;
	std::cout << "UT - " << sb.putWord(0, 8, true, "UT") << std::endl;
	std::cout << "HEN - " << sb.putWord(0, 4, true, "HEN") << std::endl;
	std::cout << "ELS - " <<  sb.putWord(2, 3, true, "ELS") << std::endl;
	std::cout << "EQUAL - " << sb.putWord(2, 3, false, "EQUAL") << std::endl;
	std::cout << "REQUALIFIED - " << sb.putWord(1, 3, false, "REQUALIFIED")
		<< std::endl;
	std::cout << "PIER - " << sb.putWord(1, 0, true, "PIER") << std::endl;
	std::cout << "PACIFY - " << sb.putWord(1, 0, false, "PACIFY") << std::endl;
	std::cout << "PACIFYING - " << sb.putWord(1, 0, false, "PACIFYING")
		<< std::endl;
	std::cout << "IS - " << sb.putWord(1, 1, false, "IS") << std::endl;
	std::cout << "YE - " << sb.putWord(0, 2, false, "YE") << std::endl;
	std::cout << "OXYPHENBUTAZONE - " <<
		sb.putWord(0, 0, true, "OXYPHENBUTAZONE") << std::endl;


	//TODO Make it so that words actually have to connect.


	sb.printBoard();

	return 0;
}