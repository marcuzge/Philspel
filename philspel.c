/*
 * Include the provided hashtable library
 */
#include "hashtable.h"

/*
 * Include the header file
 */
#include "philspel.h"

/*
 * Standard IO and file routines
 */
#include <stdio.h>

/*
 * General utility routines (including malloc())
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines
 */
#include <string.h>

/*
 * this hashtable stores the dictionary
 */
HashTable *dictionary;

/*
 * the MAIN routine.  You can safely print debugging information
 * to standard error (stderr) and it will be ignored in the grading
 * process, in the same way which this does.
 * Worked in a study group with Luyao.
 */
int main(int argc, char **argv){
  if(argc != 2){
    fprintf(stderr, "Specify a dictionary\n");
    return 0;
  }

  /*
   * testing!!!
   */
  // fprintf(stderr, "%d\n", stringEquals("61b", "61c")); //same size
  // fprintf(stderr, "%d\n", stringEquals("hello", "hi")); //first string longer
  // fprintf(stderr, "%d\n", stringEquals("6", "61c")); //second string longer
  // fprintf(stderr, "%d\n", stringEquals("hello", "hello")); //equal strings

  /*
   * Allocate a hash table to store the dictionary
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(2255, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();

  /* main in C should always return 0 as a way of telling
     whatever program invoked this that everything went OK
     */
  return 0;
}

/*
 * You need to define this function. void *s can be safely casted
 * to a char * (null terminated string) which is done for you here for
 * convenience.
 * http://www.cs.berkeley.edu/~jrs/61b/lec/22
 */
unsigned int stringHash(void *s){
  char *string = (char *) s;
  int i;
  int hash_code = 0;
  for (i = 0; i < strlen(string); i++) {
    hash_code = (127 * hash_code + (int)string[i]) % 16908799;
  }
  return hash_code;
}

/*
 * You need to define this function.  It should return a nonzero
 * value if the two strings are identical (case sensitive comparison)
 * and 0 otherwise.
 */
int stringEquals(void *s1, void *s2){
  char *string1 = (char *) s1;
  char *string2 = (char *) s2;
  if (strlen(string1) != strlen(string2)) {
    return 0;
  }
  while (*string1 != '\0' && *string2 != '\0') {
    if (*(string1++) != *(string2++)) {
      return 0;
    }
  }
  return 1;
}


/*
 * this function should read in every word in the dictionary and
 * store it in the dictionary.  You should first open the file specified,
 * then read the words one at a time and insert them into the dictionary.
 * Once the file is read in completely, exit.  You will need to allocate
 * (using malloc()) space for each word.  As described in the specs, you
 * can initially assume that no word is longer than 60 characters.  However,
 * for the final 20% of your grade, you cannot assumed that words have a bounded
 * length You can NOT assume that the specified file exists.  If the file does
 * NOT exist, you should print some message to standard error and call exit(0)
 * to cleanly exit the program. Since the format is one word at a time, with
 * returns in between, you can
 * safely use fscanf() to read in the strings.
 * http://www.tutorialspoint.com/c_standard_library/c_function_fgetc.htm
 */
void readDictionary(char *filename){

  FILE* inpfile;
  char* stack = NULL;
  char* word = NULL;
  int s_size = 60;
  int i = 0;
  int ch;

  inpfile = fopen(filename, "r");
  if (inpfile == NULL) {
    fprintf(stderr, "%s\n", "File does not exist.");
    exit(0);
  }

  stack = malloc(sizeof(char) * s_size);
  while ((ch = fgetc(inpfile)) != EOF) {
    if (i > s_size - 1) {
      s_size *= 2;
      stack = realloc(stack, s_size * sizeof(char));
    } else if (ch != '\n') {
      stack[i++] = ch;
    } else {
      stack[i++] = '\0';
      word = stack;
      insertData(dictionary, word, word);
      s_size = 60;
      i = 0;
      stack = malloc(s_size * sizeof(char));
    }
  }

  free(stack);
  fclose(inpfile);
}


/*
 * This should process standard input and copy it to standard output
 * as specified in specs.  EG, if a standard dictionary was used
 * and the string "this is a taest of  this-proGram" was given to
 * standard input, the output to standard output (stdout) should be
 * "this is a teast [sic] of  this-proGram".  All words should be checked
 * against the dictionary as they are input, again with all but the first
 * letter converted to lowercase, and finally with all letters converted
 * to lowercase.  Only if all 3 cases are not in the dictionary should it
 * be reported as not being found, by appending " [sic]" after the
 * error.
 *
 * Since we care about preserving whitespace, and pass on all non alphabet
 * characters untouched, and with all non alphabet characters acting as
 * word breaks, scanf() is probably insufficent (since it only considers
 * whitespace as breaking strings), so you will probably have
 * to get characters from standard input one at a time.
 *
 * As stated in the specs, you can initially assume that no word is longer than
 * 60 characters, but you may have strings of non-alphabetic characters (eg,
 * numbers, punctuation) which are longer than 60 characters. For the final 20%
 * of your grade, you can no longer assume words have a bounded length.
 */
void processInput(){

  char* stack = NULL;
  int ch;
  int size = 60;
  int i = 0;
  char* all_but_first;
  char* all_lower;
  
  stack = malloc(sizeof(char) * size);
  while((ch = fgetc(stdin)) != EOF){

    if(!isalpha(ch)) {       //non alphabet characters as word breaks.
      if (i == 0) {
        fprintf(stdout, "%c", ch);
      } else {
        stack[i++] = '\0';
        all_but_first = allButFirstLower(stack, i);
        all_lower = allToLower(stack, i);

        if (findData(dictionary, stack) != NULL 
          || findData(dictionary, all_but_first) != NULL 
          || findData(dictionary, all_lower) != NULL) {
          fprintf(stdout, "%s", stack);
        } else {
          fprintf(stdout, "%s", stack);
          fprintf(stdout, "%s", " [sic]");
        }
        fprintf(stdout, "%c", ch);
        free(all_but_first);
        free(all_lower);
      }
      size = 60;
      i = 0;
      free(stack);
      stack = malloc(size * sizeof(char));

    } else if (i > size - 1) {
      size *= 2;
      stack = realloc(stack, size * sizeof(char));
    } else {
      stack[i++] = ch;
    }

  }
  if (i > 0) {
    stack[i++] = '\0';
    all_but_first = allButFirstLower(stack, i);
    all_lower = allToLower(stack, i);
    fprintf(stdout, "%s", stack);

    if(findData(dictionary, stack) != NULL 
      || findData(dictionary, all_but_first) != NULL
      || findData(dictionary, all_lower) != NULL) {
    free(stack);
    free(all_but_first);
    free(all_lower);

    return;

    } else {
    fprintf(stdout, "%s", " [sic]");
    free(stack);
    free(all_but_first);
    free(all_lower);
    return;
    }
  }
  free(stack);
  return;
}

/* helper function.
 * lower all but first character.
 * http://stackoverflow.com/questions/4052840/most-efficient-way-to-make-the-first-character-of-a-string-lower-case
 * http://www.tutorialspoint.com/cprogramming/c_do_while_loop.htm
*/
char* allButFirstLower(char* ch, int i) {
  char* stack;
  char* headPointer;
  stack = malloc(sizeof(char) * i);
  headPointer = stack;
  *stack++ = *ch++;
  i -= 1;
  do {
    *stack++ = tolower(*ch++);
    i--;
  }while(i != 0);
  return headPointer;
}

/* helper function.
 * lower all characters.
 * http://stackoverflow.com/questions/4052840/most-efficient-way-to-make-the-first-character-of-a-string-lower-case
*/
char* allToLower(char* ch, int i) {
  char* stack;
  char* headPointer;
  stack = malloc(sizeof(char) * i);
  headPointer = stack;
  do {
    *stack++ = tolower(*ch++);
    i--;
  }while(i != 0);

  return headPointer;
}
