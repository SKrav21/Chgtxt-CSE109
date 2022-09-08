/*
 * chgTxt C program
 * Program 0 assignment
 * CSE109 Fall 2021
 * student ID (e.g., idk321): swk324 
 * student Last name: Kravitz
 * student First name: Steven
 * gitHub ID: 78743246
 */

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*
Function works by evaluating if a function is a lowercase letter, uppercase letter, or not a letter. If it is a lowercase letter, 32 is subtracted from them
which makes it the same letter but uppercase on the ASCII table. The opposite happens with the uppercase characters as 32 is added to them.
*/
void toggleLetters(char *buffer, size_t length) {
	for(int i = 0; i < length; i++){
		if(buffer[i] >= 'A' && buffer[i] <= 'Z') {
			buffer[i] = buffer[i] + 32;
		}
		else if(buffer[i] >= 97 && buffer[i] <= 122) {
			buffer[i] = buffer[i] - 32;
		}
	}
}
/*
Functions works by taking the first value of the buffer and switching it with the last value, then taking the second value and switching it
with the second to last value and so on until the middle of the buffer
*/
void flipLine(char *buffer, ssize_t length) {
	/*Essentially the same functionality of the methods I used in Java to reverse arrays in CSE 17*/
	int i = 0;
	int j = length - 2;
	char temp = 'x';
	while(i < j) {
		temp = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = temp;
		i++;
		j--;
	}
}
/* Could not get any of the function to flip word to work
size_t nextSpace(char *buffer, size_t length) {
	for(size_t i = 0, char c = buffer[i]; i < length; i++) {
		if (c == ' ') {
			return i;
		}
		c = buffer[i];
	}
	return length - 1;
} 
*/
void flipWord(char *buffer, size_t length) {
	/*
	size_t start = 0;
	size_t space = nextSpace(buffer, length);
	char c = buffer[space];
	for(int i = 0; c == ' '; i++) {
		flipLine(&buffer[start], space - start);
	}
	*/
}
/*
Function works by running through a for loop that continues until a null value is reached. When on the for loop, the function will continuosly remove the next 
character in the buffer so long as the next character is a digit.
*/
void deleteDigits(char *buffer, size_t length) {
	/*Same algorithm as a method I wrote for Java for a program in CSE17*/
	for(int i = 0; buffer[i] != 0; i++) {
		while(isdigit(buffer[i])) {
			for(int j = i; buffer[j] != 0; j++) {
				buffer[j] = buffer[j+1];
			}
		}
	}
}
/*
Program will check if the first character is a dash. The argv checks the second character for one of the valid options of t, l, w, or d. Should there be errors,
the function will print an error message and exit smoothly.
*/
void parseArgs (int argc, char *argv[], int *revWord, int *revLine, int *toggle, int *delete) {
	for(int i =1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if(argv[i][4] == 'e') {
				fprintf(stderr, "Invalid command line option");
				exit (3);
			}
			if (argv[i][1] == 't') {
				*toggle = 1;
			}
			else if (argv[i][1] == 'l') {
				*revLine = 1;
			}
			else if (argv[i][1] == 'w') {
				*revWord = 1;
			}
			else if (argv[i][1] == 'd') {
				*delete = 1;
			}
			else {
				fprintf(stderr, "Invalid command line option");
				exit(2);
			}
		}
		else {
			fprintf(stderr, "Invalid command line option");
			exit(1);
		}
	}
}
/*
The fucntion creates the buffer as null and the length and numchars as 0. The function then will continuously use the getline function so long as the user did not hit
ctrl D. The fucntion will send the buffer to the various functions to be altered as per the options selected by the user.
*/
void alterInput(int revWord, int revLine, int toggle, int delete) {
	char *buffer = NULL;
	size_t length = 0;
	ssize_t numchars = 0;

	while((numchars = getline(&buffer, &length, stdin)) != -1) {
		if(toggle > 0) {
			toggleLetters(buffer, numchars);
		}
		if(revLine > 0) {
			flipLine(buffer, numchars);
		}
		if(revWord > 0) {
			flipWord(buffer, numchars);
		}
		if(delete > 0) {
			deleteDigits(buffer, numchars);
		}
		printf("%s", buffer);
	}	
	if (buffer) free(buffer);
}
 
int main(int argc, char **argv) {
  int revWord = 0, revLine = 0, toggle = 0, delete = 0;
  parseArgs(argc, argv, &revWord, &revLine, &toggle, &delete);
  alterInput(revWord, revLine, toggle, delete);
  return 0;
}

