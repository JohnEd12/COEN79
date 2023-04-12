// John Edgar
// COEN 79

#include <cstring>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(){
    string input;
    // char array
    char ch[50];
    // keeps track of the guess count
    int gCount;
    // g is the integer that the computer suggestes based on the rand() function
    int g;
    cout << "Type a number 1 through 20\n";
    cin.get();
	
    while(1) {
	srand(time(NULL));
	// assigns a random number to g 
	g = rand() % 21;
	cout << "Is the number " << g << "? Y or N \n";
	// string input now checks for Y or N 
	getline(cin, input); 
	// statements check to see what string input has (either Y or N) then makes decisions based on that answer 
	if(input == "Y") {
            gCount++;
            cout << "it took me " << gCount << " guesses! \n";
            break;
        } else {
            gCount++;
	    //continue;
            
        }	
    }
	return 0;
}
