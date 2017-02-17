#ifndef _PHILSPEL_H
#define _PHILSPEL_H

extern struct HashTable *dictionary;

extern unsigned int stringHash(void *string);

extern int stringEquals(void *s1, void *s2);

extern void readDictionary(char *dictName);

extern void processInput();

extern char* allButFirstLower(char* str, int i);

extern char* allToLower(char* str, int i);

#endif
