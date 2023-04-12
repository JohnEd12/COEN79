// John Edgar
// COEN 79 MWF 8am 


#include "sequence1.h"
#include <cassert>
#include <cmath>

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3{
	// constructor 
	sequence::sequence(){
		current_index = 0;
        	used = 0;	
	}
	// index is set to zero  
	void sequence::start(){
		current_index = 0;
	}
	// finds the last item in the sequence
	void sequence::end(){
		int i;
		for(i = CAPACITY-1; i >= 0; i--) {
            		current_index = i;
            		if(is_item() == true) {
               			break;
			}
		}
	}
	// returns current position
	sequence::value_type sequence::current() const{
		assert(is_item() == true);
		return data[current_index];
	}
	// increases the value by 1
	void sequence::advance(){
		assert(is_item());
		if( current_index < (CAPACITY-1) ){
			current_index++;
		}
		
	}
	// confirms there is a valid current value
	bool sequence::is_item() const{
		if(current_index < used){
			return true;
		}
		else{
			return false;
		}
	}
	// inserts an item to either the front or shifts all the items over and inserts it at the current index 	
	void sequence::insert(const value_type& entry){
		assert(size() < CAPACITY);
		if(is_item() == false){
			current_index = 0;
		}else{
			 for(int i = used; i > current_index; i--) {
				data[i] = data[i-1];
			 }	
		}
		// after the items are shifted (or there isn't any) the item is inserted into the index
		data[current_index] = entry;
        	used++;		

	}
	// shifts all the items over and attaches the entry behind the current index
	void sequence::attach(const value_type& entry){
		assert(size() < CAPACITY);
		if(is_item() == false){
            		data[used+1] = entry;
		}else{
			// this for loop pushes all the items forward so the new entry can attach at the behind
                	for(int j = used-1; j > current_index; --j){
				data[j+1] = data[j];
			}
			data[current_index+1] = entry;
		}
                used++;		
	}
	// removes the current item, for loop shifts all the data after the item is removed and decrements 'used'
	void sequence::remove_current(){
		assert(is_item() == true);
		for(int i = current_index+1; i < used; i++) {
            		data[i-1] = data[i];
        	}
		used--;
	}
	// inserts entry to the front but the rest of the sequences is moves up before hand 
	void sequence::insert_front(const value_type& entry){
		assert(size() < CAPACITY);
		for(int i = used; i >= 0; i--) {
            		data[i] = data[i-1];
		}
		data[0] = entry;
		used++;
		current_index = 0;
	}
	// moves current index to the back and then attaches it
	void sequence::attach_back(const value_type& entry){
		assert(size() < CAPACITY);
		for(int i = 0; i <= used; i++) {
                        data[i-1] = data[i];
			// since its in the for loop the index will find the end of the sequences
                	current_index++;
		}
		data[current_index] = entry;
		used++;
	}
	// removes the front item and moves the rest of the sequence	
	void sequence::remove_front(){
		assert(size() < CAPACITY);
		current_index = 0;
		for(int i = 0; i <= used; i++) {
                        data[i-1] = data[i];
                        //current_index++;
                }
		used--;			
	}
	// returns the number of entries, this is tracked by the used variable
	sequence::size_type sequence::size() const{
		return used;
	}
	// combines sequences 
	sequence operator+(sequence& lhs, sequence& rhs){
		sequence seq(lhs);
        	sequence right(rhs);
        	right.start();
		//uses the attach function to combine the sequences
        	for(int i = 0; i < right.size(); i++) {
            		seq.attach(right.current());
       		     	right.advance();
        	}
        	return seq;		
	}
	// attaches one sequences to another by using the attach function and the current index. Also the advance function is used to go to the next item
	sequence operator+=(sequence& lhs, sequence& rhs){
		rhs.start();
        	for(int i = 0; i < rhs.size() - 1; i++) {
            		lhs.attach(rhs.current());
            		rhs.advance();
        	}
        	return lhs;
	}
	// returns the value of the index
	sequence::value_type sequence::operator[](int index) const {
                assert(index < used);
                return data[index];
        }
	// find the sum of the sequence and divides it by the number of items (used) to find the mean
	double sequence::mean() const{
		double sum;

        	for(int i = 0; i < used; i++) {
            		if(is_item() == true) {
                		sum += data[i];
            		}
        	}
        	cout << sum/used << endl;
        	return sum/used;
	}
	// uses the standard deviation equation and re do's the mean value		
	double sequence::standardDeviation() const{
		int sum = 0;
        	for(int i = 0; i < used; i++) {
            		sum += data[i];
        	}
        	double mean = (double)sum / (double)used;

       		double sqDiff = 0;
        	for(int j = 0; j < used; j++) {
			sqDiff += (data[j] - mean) * (data[j] - mean) ;
		}	

	}
	// calculates the sume of the sequence
	sequence::value_type summation(const sequence &s){
		sequence t(s);
        	t.start();
        	int sum = 0;
		// for loop lets the sum be added by each item in the sequence
        	for(int i = 0; i < t.size(); i++) {
           		sum += t.current();
			// goes to the next item
            		t.advance();
        	}
        	return sum;
	}			
}

	

