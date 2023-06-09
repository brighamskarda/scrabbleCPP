cmake_minimum_required(VERSION 3.18)
project(scrabbleCPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(scrabbleCPP src/BoardState.cpp src/constants.h src/RandomGames.cpp src/scrabble.cpp src/ScrabbleBoard.cpp src/highScoreWords/HighScoreWords.cpp)
