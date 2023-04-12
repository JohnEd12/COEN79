//John Edgar
//COEN 79

#include <string>
#include <cstring>
#include <iostream>

using namespace std;
// this program will dictate how many alphanumeric and non-alphanumeric are in a word
int main(){
        int alphaN = 0;
        int noAlphaN = 0;
        char ch;
	// char pointer
        char *strp;
	// char string
        char sttr[50];
	string str1;
	
	cout << "Enter a word: ";
	// get line function retrieves the word and puts it into the str1 string
	getline(cin, str1);
	// sttr string holds the word written
	strcpy(sttr, str1.c_str());
	// this look means the strp pointer is now pointing at the sttr array and will be using the array to go through each character and see if it is alpha numeric or not
	for(strp = sttr; *strp != '\0'; strp++){
		ch = *strp;
		if(iswalnum(ch)){
			alphaN++;					
		}else if(ch == ' '){
			continue;
		}else{
			noAlphaN++;
		}		
	}
	cout << "Alphanumeric Count: " << alphaN << "\n";
	cout << "Non Alphanumeric Count: " << noAlphaN << "\n";	
}                   
