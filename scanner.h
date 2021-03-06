/* scanner
1. to translate the sequence of characters in the definition file
into a sequence of 'symbols'
2. symbols => keyword, name, number, punctuation
3. skipping comments, spaces, line breaks
*/

#ifndef scanner_h
#define scanner_h

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "names.h"
#include "network.h" // to make use of devicekind

using namespace std;

// For symbols describing devices
// Use the definition provided in network.h instead!
typedef enum {namesym, numsym, devsym, consym, monsym,
	comma, semicol, colon, equals, leftbrk, rightbrk, fullstop, greaterthan,
	badsym, eofsym, slash, eoline } symbol;

	/*
	for unit testing comparison
	0 		= namesym
	1 		= numsym
	2,3,4	= dev, con, mon
	5		= ,
	6		= ;
	7		= :
	8		= =
	9		= (
	10		= )
	11		= .
	12		= >
	13		= badsym
	14		= eofsym
	15		= /
	16		='\n'
	*/

typedef int name;


class scanner {
private:
    ifstream inf; //input definition file
    char curch; //current input character
	char prevch; //previous input character
    bool eofile; //true when end of file is reached
    int linenum; //line number

    void skipspaces(); //skips spaces
    void skipcomments(); //skips comments
    void getnumber(int& num); //reads number
    void getname(name& id, bool& is_keyword); 	//reads name

	names* _nmz; // pointer to names class
	vector<string>	lines;

public:
    scanner(names* nmz, // pointer to names class
            const char* defname); // name of the def file
            /*the constructor takes care of openning the definition file
            as well as initialisation any global scanner variables */

    ~scanner(); // destructor to close file

    void getsymbol(symbol& s,   // symbol read from the file
                   name& id,    // name id if it is a name
                   int& num);   // value if it is a number
    // return successive symbols in the definition file

	void skipcolon();			//skip if curch is a ':'
	void skip_dueto_error(symbol& s, name& id, int& num, bool print = true);
	void print_line_error(int n);
	// Functions for unit testing
	void print_curch();
	bool is_eofile();
};


#endif /* scanner_h */
