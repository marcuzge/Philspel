# Philspel

CS61C Spring 2016 Project 1

Philspel is a very simple and silly spelling checker. It accepts a single command line argument, the name of a dictionary to use. This dictionary consists of a list of valid words to use in checking the input. Philspel processes standard input and copies it to standard output. For each word (sequence of letters unbroken by any non-letter character) in the input, it looks that word, that word converted entirely to lowercase letters, and that word with all but the first letter converted to lowercase. If any of the three variations are found in the dictionary, the word is copied to standard output. Otherwise, the word is copied to standard output, with the string " [sic]" (without the quotation marks but with the spaces appended). All other input is copied to standard output unchanged.

The assignment is to complete the implementation of philspel. To do this, I implemented 4 functions in philspel.c: stringHash(void *s), stringEquals(void *s1, void *s2), readDictionary(char *filename), and processInput().

Just as a reminder, this projected is to be completed individually.
