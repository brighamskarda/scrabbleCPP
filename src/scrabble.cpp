#include <iostream>
#include "BoardState.h"
#include "ScrabbleBoard.h"

int main() {
	std::cout << "Hello World" << std::endl;

	ScrabbleBoard sb;
	sb.hello();

	BoardState bs;
	bs.hello();
	return 0;
}