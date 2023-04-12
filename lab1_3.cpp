// John Edgar 
// COEN 79

#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <fstream>
using namespace std;

//This program opens a file, reads it, erases all the non alphanumeric numbers and for all words 10+ characters long the it will print that word in upper case
int main(int argc, char* argv[]){
	string s = "";
	char ch;
	int i;
	fstream file;
	// file opens
	file.open(argv[1]);
	while(file >> s){
		// check to see if a word is 10 characters or longer, if so it becomes uppercase 
		if(s.length() >= 10){
			for(i = 0; i< s.length(); i++){
				ch = s[i];
				// erases the non-alphanumeric characters
				if(!isalpha(ch)){
					s.erase(i,1);
					i--;
				}else{
					putchar(toupper(ch));
				}
			}
			cout << "\n";
		}
	}
	// closes file
	file.close();
	return 0;
} 
