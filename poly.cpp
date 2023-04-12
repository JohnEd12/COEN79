// John Edgar 
// COEN 79 MWF 8am
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>
#include <cmath>
#include <climits>
#include <cstdlib>
#include "poly.h"

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4{

	const unsigned int polynomial::MAXIMUM_DEGREE;


// Constructor
polynomial::polynomial(double c, unsigned int exponent){
	assert(exponent <= MAXIMUM_DEGREE);
	clear();
	// c is a parameter that gives us a value in the coef bag
	coef[exponent] = c;
	// current degree is the exponent of the parameter
	current_degree = exponent; 
}
// updates the current degree
void polynomial::update_current_degree(){
	int w = 0;
        // this for loop finds the current degree by going through each coefficient and counting while keeping a counter w
	for(int i = 0; i < MAXIMUM_DEGREE; i++) {
		if(coef[i] != 0) {
			w = i;
                }
        }
       	current_degree = w;
} 

// Modification Member Functions 
void polynomial::assign_coef(double c, unsigned int exponent) {
	assert(exponent <= MAXIMUM_DEGREE);
	coef[exponent] = c;
	update_current_degree();	 
}
// adds to the coefficient 
void polynomial::add_to_coef(double amount, unsigned int exponent){
	assert(exponent <= MAXIMUM_DEGREE);
	coef[exponent] += amount;
	update_current_degree();
}
// makes the whole coef[] zero
void polynomial::clear( ) {
	for(int i = 0; i < MAXIMUM_DEGREE; i++) {
            coef[i] = 0;
        } 
        update_current_degree(); 
}
// Constant Member Functions
polynomial polynomial::antiderivative( ) const {
 	assert(degree() < MAXIMUM_DEGREE);
	polynomial sew;	
        int i;
	for(i=0; i < MAXIMUM_DEGREE - 1; i++){
		sew.coef[i+1] = coef[i]/(i+1);
	}
	sew.coef[0] = 0;
    	sew.update_current_degree();
	return sew;
}
// finds the coefficient by the exponent 
double polynomial::coefficient(unsigned int exponent) const {
	if(exponent > MAXIMUM_DEGREE) {
            return 0;
        } else {
            return coef[exponent];
        }  
}
// creates the value of the definite integral
//
double polynomial::definite_integral(double x0, double x1) const {
	polynomial sew = antiderivative();
	return sew.eval(x0) - sew.eval(x1);
}

// find the derivative by multiplying the coef of one higher of a degree
polynomial polynomial::derivative( ) const {
	polynomial sew;
	for(int i = 0; i < MAXIMUM_DEGREE - 1; i++) {
            sew.coef[i] = coef[i+1]*(i+1);
        }
        sew.update_current_degree();
        return sew;
}

// multiplies it by the pow it wants it to be
double polynomial::eval(double x) const {
	double result = 0;
   	int i;
    	for(i=0; i < MAXIMUM_DEGREE; i++){
      		result += (coef[i] * pow(x, i) );
    	}
	return result;
}

bool polynomial::is_zero( ) const {
	return (coef[current_degree] == 0.0);
}

unsigned int polynomial::next_term(unsigned int e) const {
    	int i;    
	// e is the term and this finds the next terms n value that is larger than e but not equal to 0
	// this is why i starts at e+1 
	for(i = e+1; i<MAXIMUM_DEGREE; i++){
      		if(coef[i] > 0) return i;
    	}
	return 0;
}
// accesses the prev term 
unsigned int polynomial::previous_term(unsigned int e) const {
	int i;
    	// e is the term and this finds the next terms n value that is smaller than e but not equal to 0
    	// this is why i starts at e-1 
  	for(i = e-1; i>0; i--){
      		if(coef[i] > 0) {
			return i;
      		}
    	}
	return UINT_MAX;
  }
// NON MEM Operations
polynomial operator +(const polynomial& p1, const polynomial& p2){

	polynomial sew;
	// coefficients are added
        for(int i = 0; i < polynomial::MAXIMUM_DEGREE; i++) {
            sew.add_to_coef(p1.coefficient(i) + p2.coefficient(i), i);
        }
        sew.update_current_degree();
	// object is returned 
        return sew;

}

polynomial operator -(const polynomial& p1, const polynomial& p2) {
	polynomial sew;
	// coefficients are subtracted, each coefficient is subtracted bc it goes through the whole loop til max degree
        for(int i = 0; i < polynomial::MAXIMUM_DEGREE; i++) {
            sew.add_to_coef(p1.coefficient(i) - p2.coefficient(i), i);
        }
        sew.update_current_degree();
        // object is returned
	return sew;
}
// non member operator*
polynomial operator *(const polynomial& p1, const polynomial& p2) {
	
        polynomial sew;
        int i;
	int j;
	// goes through the loop by counting the degree for mathematical purposes
        // this way the coefficients can be multipled the correct number of times
	for(i = 0; i <= p1.degree(); i++) {
                for(j = 0; j <= p2.degree(); j++) {
                    sew.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i+j);
                }
        }
	return sew;
}

// NON MEM 
std::ostream& operator << (std::ostream& out, const polynomial& p){
	int i = p.degree();
	for (i; i >= 0; i--) {
	// Conditionals are used to determine what coefficient to assign to the x value  
	// i is the degree and 
		if (p.degree() == 0) {
			cout << p.coefficient(i);
		}
		else if (p.coefficient(i) != 0) {
			if (i == p.degree()) {
				if (i > 1) {
					out << p.coefficient(i) << "x^" << i << " ";
                   		}			
				else if (i == 1) {
        		                out << p.coefficient(i) << "x ";
                    		}
				else if (i == 0) {
					out << p.coefficient(i) << " ";
                    		}

		}
		// used to determine the value sign in front of the number 
		else if (i < p.degree() && i > 1) {
			// sees if the number is negative, if so it puts a - sign
			if (p.coefficient(i) < 0) {
				out << "- " << p.coefficient(i)*-1;
                    	}
			// sees if the number is a positive, if so it puts a + sign
			else if (p.coefficient(i) >= 0 && p.previous_term(i)!=0){
				out << "+ " << p.coefficient(i);
                    	}
					// prints the x and i (which is the degree)
				out << "x^" << i << " ";
		} 
		// conditional is made for this because if the degree is 1 then we only need x instead of x^1
		else if (i == 1) {
			// same as above, these conditionals see if the coefficient is neg or ppos
			if (p.coefficient(i) < 0) {
				out << "- " << p.coefficient(i) * -1;
                    	}
			else if(p.coefficient(i) >= 0 && p.previous_term(i)!=0) {
				out << "+ " << p.coefficient(i);
                    	}
		out << "x ";
		}
		// no x or degree 
		else if (i == 0) {
			/// same as above, these conditionals see if the coefficient is neg or pos
			if (p.coefficient(i) < 0) {
				out << "- " << p.coefficient(i) * -1;
                  	}
			else if(p.coefficient(i) >= 0 && p.previous_term(i)!=0){
				out << "+ " << p.coefficient(i);
                    	}
		}
			}
		}
		return out;
}

} 
