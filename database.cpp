// John Edgar
// MWF 8am 
// COEN 79

#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    	   
    database::database(const database &src) {		
        Debug("Copy constructor..." << std::endl);
        // copies the src values of used and aloc over
        used_slots = src.used_slots;				
	aloc_slots = src.aloc_slots;
	// creates and allocates memory for a new array and copies over the data 
	company_array = new company[aloc_slots];		
	*company_array = *src.company_array; 		
    }
    
    
    database& database::operator= (const database &rhs) { 	
        Debug("Assignment operator..." << std::endl);
    	// checks to see if its already equal
	if(this == &rhs) {				
		return *this;		
	}
	// copies over the used and aloc values
	used_slots = rhs.used_slots;				
	aloc_slots = rhs.aloc_slots;
	// deletes the array 
	delete[] company_array;					
	std::copy(rhs.company_array, rhs.company_array + used_slots, company_array);		
	return *this;										
    }
    
    // deconstructor 
    database::~database() {
	// deletes it and sets the variables to 0		
        delete[] company_array;	
	used_slots = 0;		
	aloc_slots = 0;
    }
    
    
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; 
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; 
        // new array is made with the new capacity 
        aloc_slots = new_capacity;				
        company *temp = new company[aloc_slots];
	// copyihg the old array into the new one			
	std::copy(company_array, company_array + used_slots, temp);	
	// deletes the old array
	delete[] company_array;						
	company_array = temp;					
    }
    
    
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
       
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }
	if(used_slots == aloc_slots) {	
		reserve(aloc_slots + 1);	
	}
	// inserts the entry into the array
	company temp = company(entry);	
	company_array[used_slots] = temp;
	// increases the counter used_slots	
	used_slots++;				
	return true;
    }
    
    
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {	
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);		
	
        size_type pos = search_company(company);			
     	// position doesn't exist
	if(pos == COMPANY_NOT_FOUND) {					
		return false;
	} else {
		// inserts at the position given
		company_array[pos].insert(product_name, price);		
	}
	return true;
    }
    
    
    bool database::erase_company(const std::string &company) {			
        
        size_type company_index = search_company(company);			
        // index doesnt exist
        if(company_index == COMPANY_NOT_FOUND) {				
		return false;
	} 
	// loops through the array 
	for(size_type i = company_index; i < used_slots - 1; i++) { 		
		company_array[i] = company_array[i+1];
	}
	used_slots--;								
	return true;
    }
    
    
    bool database::erase_item(const std::string& cName, const std::string& pName) {  
        
        assert(cName.length() > 0 && pName.length() > 0);

        size_type company_index = search_company(cName);	
	if(company_index == COMPANY_NOT_FOUND) {			
		return false;
	}
	// has the company index so we use the erase function
	company_array[company_index].erase(pName);			
	return true;	
    }
    
    
    
    database::size_type database::search_company(const std::string& company) {		
        assert(company.length() > 0);
	// loops through the array to find the company and its index
        for(size_type i = 0; i < used_slots; i++) {					
		if(company_array[i].get_name() == company) {				
			return i;
		}
	}
        return COMPANY_NOT_FOUND;							
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif

