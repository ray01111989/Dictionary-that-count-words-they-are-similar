
//Name: Rawad Bader
//Date: 11/14/2018
//Class: CSE224
//This program reads text from standard input and counts how many times each phrase appears.
//Steps: it changes every letter to uppercase, ignores the characters ( ) ' " -, turns tabs and new lines into
//spaces, and collapses runs of spaces into a single space. A phrase ends at any separator (, . ; : ? !).
//Each phrase is saved in a dictionary; when the same phrase appears again its counter goes up, and a new
//phrase is added with a counter of 1. Finally the dictionary is sorted by phrase length (shortest first)
//and printed.
//
//Build:  gcc -Wall -o p4 p4.c
//Run:    ./p4 < input.txt
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define PHRASE_MAX 201   // longest phrase we store, including the ending '\0'
#define DICT_SIZE 1000   // most different phrases the dictionary can hold

// Reads one character from standard input and converts it to uppercase (EOF is passed through unchanged)
int getupperchar()
{
	int c = getchar();
	c = toupper(c);
	return c;
}

// Returns true for the characters that count as white space: tab, new line, and space
bool isWhiteSpace(int c)
{
	if (c=='\n' || c=='\t'|| c==' ')
		return true;
	else
		return false;
}

// Returns true for the characters that are dropped from the text: ( ) ' " -
bool ShouldIgnore(int c)
{
	if (c=='(' || c==')' || c=='\'' || c=='\"' || c=='-')
		return true;
	else
		return false;
}

// Returns true for the characters that end a phrase: , . ; : ? !
int isSeperator(int c)
{
	if (c==',' || c=='.' || c==';' || c==':' || c=='?' || c=='!')
		return true;
	else
		return false;
}

// Gets the next usable character: uppercased, skipping ignored characters, with any white space turned into a space
int getinput()
{
	int c = getupperchar();
	// Keep reading while the character is one we ignore (a loop instead of recursion, so a very long run of
	// ignored characters cannot overflow the stack)
	while (c != EOF && ShouldIgnore(c) == true)
		c = getupperchar();
	if (isWhiteSpace(c) == true){
		c = ' ';
	}
	return c;
}

// Reads one phrase into str (which must hold at least length characters) and returns the character that ended it
// (a separator, or EOF). Leading and trailing spaces are removed and runs of spaces become a single space.
int getPhrase(char *str, int length)
{
	int c=getinput();
	// Skip spaces at the start of the phrase
	while (isWhiteSpace(c))
		c=getinput();

	int i=0;
	while (!isSeperator(c) && c != EOF){
		// Keep one slot free for the ending '\0'. Skip a space that follows another space.
		if (i < length - 1 && !(c == ' ' && i > 0 && str[i-1] == ' ')){
			str[i] = c;
			i++;
		}
		c=getinput();
	}
	// Remove a space left at the end of the phrase
	if (i > 0 && str[i-1] == ' ')
		i--;
	str[i] = '\0';
	return c;
}

char dict[DICT_SIZE][PHRASE_MAX] = {{'\0'}};// the phrases; an empty string ('\0' first) means the slot is unused
int count[DICT_SIZE] = {0};                 // count[i] is how many times dict[i] has been seen
int dictlen=DICT_SIZE;

// Adds a phrase to the dictionary. If it is already there its counter goes up by one; otherwise it is copied
// into the first empty slot with a counter of 1. Returns the slot used, or -1 if the dictionary is full.
int insert(char *str)
{
	int i;
	for (i = 0 ; i< dictlen; i++){
		if(dict[i][0]=='\0'){          // found an empty slot: store the new phrase here
			strcpy(dict[i],str);
			count[i]++;
			return i;
		}
		if (strcmp(str,dict[i])==0){   // found the same phrase: just count it again
			count[i]++;
			return i;
		}
	}
	fprintf(stderr, "Dictionary is full; the phrase <%s> was not counted\n", str);
	return -1;
}

// Sorts the dictionary by phrase length, shortest first (bubble sort: keep swapping neighbours that are out of order)
void sort()
{
int i;
int c=1;
	while(c>0){					// repeat until a full pass makes no swaps
	c=0;
	for (i=0; i<dictlen-1 && count[i+1]>0; i++){
		if (strlen(dict[i])>strlen(dict[i+1])){
			char temp[PHRASE_MAX];
			int t;
			strcpy(temp,dict[i]);       // swap the two phrases...
			t=count[i];
			strcpy(dict[i],dict[i+1]);
			count[i]=count[i+1];
			strcpy(dict[i+1],temp);
			count[i+1]=t;               // ...and their counters
			c++;
		}
	}
	}
}

// Prints every phrase that was counted, as a 5-digit count followed by the phrase in <angle brackets>
void print(){
	int i;
	for (i=0; i<dictlen; i++){
	if (count[i]>0)
		printf("%05d <%s>\n",count[i],dict[i]);
	}
}

int main(void){
	int c;
	char s[PHRASE_MAX] = "";

	// Read phrase after phrase until the input ends, adding each one to the dictionary.
	// Empty phrases (for example from ",,") are skipped: an empty string looks like an empty dictionary slot.
	while ((c=getPhrase(s,PHRASE_MAX)) != EOF) {
		if (s[0] != '\0')
			insert(s);
	}
	// The last phrase may end at the end of the input instead of a separator; count it if it is not empty
	if (s[0] != '\0')
		insert(s);
	sort();
	print();
	return 0;
}
