The methodology behind this method is to first, find very high scoring words.
(Words that are probably 15 letters down the left side).

Then find the highest scoring words that can connect to the word we have
selected. For each row. This sometimes means that the word can exist without
its first letter and still be valid.

Then select the highest possible scoring word with the letters that we have left.

1. Create highScoreWords class. ✓✓✓
1.5. Put refreshBoard function in the ScrabbleBoard class.
2. Create a script that finds the highest scoring words down the left side.
This should find the 100 best words and put them in a vector. (100 can be
reduced to possibly increase performance). (All words should be 15 letters).
3. Create a script that gets 8 words that can connect to our big word.
4. Create a script that connects it all back to the center.
5. Create a script that plays the whole game and gets the final score for our
word.
6. Create a script that does this forever and saves the best scenario.