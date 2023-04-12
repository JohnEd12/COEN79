// John Edgar
// COEN 79 MWF 8am
#include "random.h"

namespace coen79_lab2 {
	// Assigning variables
	rand_gen::rand_gen(int seed1, int multiplier2, int increment3, int modulus4) {
		seed = seed1;
		multiplier = multiplier2;
		increment = increment3;		
		modulus = modulus4;
		
	}
	// creating a new seed value. Value of the seed is changed to the new number and that is how random numbers are produced
	void rand_gen::set_seed(int new_seed) {
		seed = new_seed;
	}
	// Forumla from camino shows us how the create a random number 
	int rand_gen::next() {
		int n = ((multiplier * seed + increment ) % modulus);
        	seed = n;
        	return n;
	}
	// prints the information of see, multipler, increment, and modulus
	void rand_gen::print_info() {
		cout << "Seed: " << seed << endl;
        	cout << "Multiplier: " << multiplier << endl;
        	cout << "Increment: " << increment << endl;
        	cout << "Modulus: " << modulus << endl;		
	}
}
