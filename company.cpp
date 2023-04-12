// John Edgar
// MWF 8am
// COEN 79

#include <cassert>
#include "company.h"

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    // initializes the company_name and the two pointers head & tail    
    company::company(const std::string& company_name) {		
        assert(company_name.length() > 0);			
        this->company_name = company_name;		
	this->head_ptr = NULL;					
	this->tail_ptr = NULL;
    }
    // copy constructor 
    company::company(const company &src) {			
        Debug("Company copy constructor..." << std::endl);
        // new head and tail pointers are made to the old head and tails can point to them
        // also we do a list copy to copy over the list to the new head and tail
	node *new_head;					
	node * new_tail;
	list_copy(src.get_head(), new_head, new_tail);		
	this->head_ptr = new_head;				
	this->tail_ptr = new_tail;
	this->company_name = src.get_name();		
    }

    // assignment operator 
    company& company::operator= (const company &src) {	
        Debug("Company assignemnt operator..." << std::endl);
        //creates a new head and tail pointer
	node *new_head;						
	node *new_tail;
	// list is copied into the new head and tail 
	list_copy(src.get_head(), new_head, new_tail);
	// now the old head and tail are assigned to the new head and tail		
	head_ptr = new_head;				
	tail_ptr = new_tail;
	company_name = src.get_name();			
    }
    
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    // insert function
    bool company::insert(const std::string& product_name, const float& price) {		
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {						
            list_init(head_ptr, tail_ptr, product_name, price);
        }
	// since the head isn't null, that means there must be a tail so we insert from the rear (which is the tail) 
        else {								
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }

    // erase function   
    bool company::erase(const std::string& product_name) {		
        assert(product_name.length() > 0);
	// temperary node 
	node *temp = list_search(head_ptr, product_name);		
	if(temp == NULL) {				
		return false;
	} 
	// means the product name was at the head so we can easily remove it
	else if (temp == head_ptr) {				
		list_head_remove(head_ptr);
	}
	// precursor to be right behind the node that has the product_name
	node *precur = head_ptr;				
	// this will make it easier to erase it
	while(precur->getLink() != temp) {			
		precur = precur->getLink();
	}
	// precur now points to the node after temp so we can now delete it 
	precur->setLink(temp->getLink());				
	delete temp;					

	return true;
    }    
    
}

