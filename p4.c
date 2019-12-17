
//Name: Rawad Bader
//Date: 11/14/2018
//Class: CSE224
//This program should first of all change all characters to uppercase letters then get rid of all the white spaces like tabs, new line, and multiple spaces. after that it should get phrases as defined after every seperator it is consedered a s phrase.Then it will save it to a dictionary and start looking for similar phrases and every time it finds one it will increment the counter but if its a new phrase it will just add it to the dictionary. lastly it will sort the dictionary according to the phrase's length.
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
int getupperchar() //converts lower case letters to uppercase letters
{
	int c = getchar();
	c = toupper(c);
	return c;
}
bool isWhiteSpace(int c)// converts TABS and new lines and spaces to just one space
{
	if (c=='\n' || c=='\t'|| c==' ')
		return true;
	else
		return false;
}
bool ShouldIgnore(int c)// ignores the characters [ (,),',",- ]
{
	if (c=='(' || c==')' || c=='\'' || c=='\"' || c=='-')
		return true;
	else
		return false;
}
int isSeperator(int c)//seperates phrases if it had these characters [ , . : ; ? ! ]
{
	if (c==',' || c=='.' || c==';' || c==':' || c=='?' || c=='!')
		return true;
	else
		return false;
}

int getinput()// gets the strings uppercased, without white spaces, and after it ignores the charaters that it should
{
	int c =  getupperchar();
	if(c==EOF)
		return c;

	if (isWhiteSpace(c) == true){
		c = ' ';
	}
	if (ShouldIgnore(c) == true){
		c = getinput();
	}
	return c;
}
int getPhrase(char *str, int length) // gets phrases after every tim it finds a seperator and stores it as a phrase
{
	int c=getinput();
	while (isWhiteSpace(c))
		c=getinput();

	int i=0;
	while (!isSeperator(c) && c != EOF){
		if (i< length){
			str[i] = c;
			i++;
		}
		c=getinput();
	}
	str[i] = '\0';
	return c;
}

char dict[1000][201] = {'\0'};// making every space equall to \0
int count[1000] = {0};
int dictlen=1000;
int insert(char *str)// insert function looks for a place where it has \0 means it dosnt have a string in it and coppies the sting into it. if the string was similar to a previous one it would add 1 to the counter.

{
	int i;
	for (i = 0 ; i< dictlen; i++){
		if(dict[i][0]=='\0'){
			strcpy(dict[i],str);
			count[i]++;
			return i;
		}
		if (strcmp(str,dict[i])==0){
			count[i]++;
			return i;
		}
	}
	return 0;
}
void sort()// sort function would compare the strings length to the one after it and swaps places it if it is longer.
{
int i;
int c=1;
	while(c>0){					// while loop will keep sorting untill there is no more strings to sort.
	c=0;
	for (i=0; i<dictlen-1 && count[i+1]>0; i++){
		if (strlen(dict[i])>strlen(dict[i+1])){
		//	printf("%s > %s\n",dict[i],dict[i+1]);
			char temp[201];
			int t;
			strcpy(temp,dict[i]);// this is to swap the strings.
			t=count[i];
			strcpy(dict[i],dict[i+1]);
			count[i]=count[i+1];
			strcpy(dict[i+1],temp);
			count[i+1]=t;
			c++;
		}
	}
	}
}
void print(){
	int i;
	for (i=0; i<dictlen; i++){
	if (count[i]>0)
		printf("%05d <%s>\n",count[i],dict[i]);	//this will print five places for the counter and the dictionary.
	}
}
int main(void){
	int c;
	char s[201];

	while ((c=getPhrase(s,201)) != EOF) {
		insert(s);
	}
	sort();
	print
