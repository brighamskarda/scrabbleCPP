# SCRABBLECPP

The goal of this repository is to find the best possible move in the board game
scrabble. That is, finding the best single word one could play under tournament
rules to get the most number of points. Written in C++ to get the speed of C,
while still having objects, without the overhead of Java.

All my code is free to use under GPL-3.0. If you do use it for a personal
project I would love to hear about it. Send comments, questions, or suggestions
to brighamskarda@gmail.com.

### Current State of Work
So far I have created a framework for placing down words and calculating their
scores. This framework ensures that all of the rules in scrabble are followed.
**There is probably still a bug or two for edge cases.** But at the very least, it
correctly finds the score for OXYPHENBUTAZONE.

```
OXYPHENBUTAZONE - 1780

OPACIFYING.....
XIS............
YE.............
PREQUALIFIED...
H.L............
EDS............
NO...T.........
BRAINWASHING...
UM...O.........
T..E.O.........
AWAKENERS......
ZONETIME.......
OOT..E.B.......
N......U.......
EJACULATING....
```

The header files are pretty
detailed. But one important feature some may find useful is the freePlay mode.
This disables the rules where a word must connect to another word, and a word
must be placed across the center on the first move.

The code is fairly optimized, the one space I see room for improvment is in the
putWord() function. This is by far the most complex section of code so far
as it essentially contains the rules for Scrabble. There is definently some
optimization to be found here later down the line.

An algorithm that essentially tries to place randome words on the board has aslo
been implemented. It sucks, but its a good starting place to get me thinking
about how I want to do this.

Next step, implement an algorithm that actually gives good results.

### Build Instructions
You need to have the following programs installed in order to complete the build
processes. 
- cmake (Version 3.18 or greater)
- gcc
Then just run cmake in the root directory of the repository.

### Gotchas
#### Different Rulesets
Originally I intended this framework to support multiple scrabble rulesets.
It is still capable of doing so for the most part. The two major limitations
to be aware of in this respect are
- Boards not of a size 15x15 must use freePlay mode. This is because in
 normal scrabble rules, the first move must be placed on the center square.
 There is not yet a way to define the center square for boards of other
 sizes.
- You can only place down 7 tiles at a time. If you want to use a ruleset
 that allows you to place down more than 7 tiles at a time, this framework
 will not work for you.

It would be fairly easy to implement the above rules. But for my purposes right
now, I don't have a need/want to work on a scrabble board with anything but the
standard rules. Suppport for different rulesets is not a gurantee for this
project.
