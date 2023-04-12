//John Edgar
//COEN 79

#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <assert.h>

using namespace std;

// reverses the string, orginally comes in as the inputed set of numbers
void reverse(string &output){
    int i;
    // this for loop swaps the first and last numbers until it reaches the middle 
    for(i=0; i<5; i++) {
    	swap(output[i], output[10-i-1]);
    }
}
// This program takes a 10 digit number and reverses it, it must be 10 though. 
int main(){
	string input;
	// person enters a 10 digi num
	cout << "Enter a 10 digit number: \n";
	// number is put into the input string
	getline(cin, input);
	// output string copies the contents in the input string
	string output = input;
	// checks to make sure the inputed digits have a lenght of 10
	assert(input.length() == 10);
	// calls the reverse function so that output string can have the reverse of input string
	reverse(output);
	// function creates the spacing using setw
	for(int i=0; i<10; i+=2) {
        	int width = i+15;
        	std:cout << setw(width) << input << setw(20) << output << "\n";
    	}

    return 0;


}
