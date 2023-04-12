// John Edgar
// COEN 79 8am

/*
NON-MEMBER functions for the statistician class:

statistician operator +(const statistician& s1, const statistician& s2)
Postcondition: The statistician that is returned contains all the numbers of the sequences of s1 and s2.

statistician operator *(double scale, const statistician& s)
Postcondition: The statistician that is returned contains the same numbers that s does, but each number has been multiplied by the scale number.
 
bool operator ==(const statistician& s1, const statistician& s2) 
Postcondition: The return value is true if s1 and s2 have the zero length. Also, if the length is greater than zero, then s1 and s2 must have the same length, the same mean, the same minimum, the same maximum, and the same sum.
*/ 

#include <cassert>
#include<iostream>
#include"stats.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2{
// implementations
	stats::stats(){
		size = 0;
		total = 0;
	}
	// adds a number to the list
	void stats::next(double r){
		// size is amount of nums in a sequence
		if(size == 0){
			// if no nums in sequence then everything is equal to the one number in the parameter
			total = r;
			size = 1;
			min = r;
			max = r;
			avg = r;
		}else{
			total += r;
			size += 1;
			if(r < min){
				min = r;
			}
			if(r > max){
				max = r;	
			}
		}	
	}
	// erases the sequence, since size is the # and total is the sum of #'s they are now set to zero
	void stats::reset(){
		size = 0;
		total = 0;
	}
	
	int stats::length() const {
		// size is how many numbers there are in the sequence
		return size;		
	}
	double stats::sum() const{
		// total is the sum of all the numbers in the sequence
		return total;
	}
	double stats::mean() const{
		// total is sum of all nums and size is # of nums 
		return (total/size);		
	}
	// returns the smallest number 
	double stats::mini() const{
		return min;
	}
	// returns the biggest number
	double stats::maxi() const{
		return max;
	}
	// conditionals based on the addition function
	stats operator +(const stats& s1, const stats& s2){
		stats sec;
		if(s1.length() == 0 && s2.length() != 0){
			return s2;
		}
		if(s1.length() != 0 && s2.length() == 0){
			return s1;
		}
		sec.size = s1.length() + s2.length();
		sec.total = s1.sum() + s2.sum();
		// if statement figures out the new max and min
		if(s1.maxi() < s2.maxi() ){
			sec.max = s2.maxi();
		}else{
			sec.max = s1.maxi();
		}
		
		if(s1.mini() < s2.mini()){
			sec.min = s1.mini();
		}else{
			sec.min = s2.mini();
		}
	}
	// conditionals based on the mulitplication function	
	stats operator *(double scale, const stats& s){
		stats sec;
		if(s.length() == 0) {
            		return s;
        	}
		sec.size = s.length();
		sec.total = scale * s.sum();
        	if(scale < 0) {
            		sec.min = scale * s.maxi();
            		sec.max = scale * s.mini();
       	 	} else {
            		sec.min = scale * s.mini();
            		sec.max = scale * s.maxi();
      		}

        	return sec;	
	}
	// returns everything equal to each other
	bool operator ==(const stats& s1, const stats& s2){
		if(s1.length() == 0 && s2.length() == 0){
			return true;
		}
		 return ( 
			(s1.length() == s2.length()) && 
			(s1.mean() == s2.mean()) && 
			(s1.mini() == s2.mini()) && 
			(s1.maxi() == s2.maxi()) && 
			(s1.sum() == s2.sum())
			);	
	}	
}

