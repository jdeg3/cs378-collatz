// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair

//#include "Collatz.h"

// ------------
// collatz_read
// ------------

std::pair<int, int> collatz_read (std::istream& r) {
    int i;
    r >> i;
    if (!r)
        return std::make_pair(0, 0);
    int j;
    r >> j;
    return std::make_pair(i, j);}

// ------------
// collatz_cycles
// ------------

int collatz_cycles (int x){

	// should never have negative input
	assert(x > 0);

	int cycles = 1;
	
	while(x > 1){
		if( x % 2 == 0)
			x = x/2;
		else
			x = x * 3 + 1;
		cycles++;
	}
	
	// should always be at least one cycle
	assert(cycles > 0);
	return cycles;
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j, int cache[]) {
    
    // my code
    int biggest = 0;

    // set i to be the min and j to be max
    if( i > j){
        int temp = i;
        i = j;
        j = temp;
    }

    while(i <= j) {
    	
    	int x;
    	
    	// cache limited so check if i is in bounds
    	if(i > 999)
    		x = collatz_cycles(i);
    		
    	// add to cache if missing
    	else if(cache[i] == 0) {
    		x = collatz_cycles(i);
    		cache[i] = x;	
    	}
    	else
    		x = cache[i];
    		
    	// if the cycles(i) is bigger than the recorded biggest, replace
    	if(x > biggest) {
    		biggest = x;
        }
        
    	i++;
    }		
    
    return biggest;}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {

	// can hold up to 1k cache values
	int cache [1000] = {};

    while (true) {
        const std::pair<int, int> p = collatz_read(r);
        if (p == std::make_pair(0, 0))
            return;
        const int v = collatz_eval(p.first, p.second, cache);
        collatz_print(w, p.first, p.second, v);}}
        
// -------------------------------
// projects/collatz/RunCollatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// -------------------------------

/*
To compile the program:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ RunCollatz.c++ -o RunCollatz

To run the program:
    % valgrind RunCollatz < RunCollatz.in

To obtain coverage of the run:
    % gcov-4.7 -b Collatz.c++ RunCollatz.c++

To configure Doxygen:
    % doxygen -g
    That creates the file "Doxyfile".
    Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    % doxygen Doxyfile
*/

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <iostream> // cin, cout

//#include "Collatz.h"

// ----
// main
// ----

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}

/*
% g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ RunCollatz.c++ -o RunCollatz



% valgrind RunCollatz < RunCollatz.in > RunCollatz.out
==17119== Memcheck, a memory error detector
==17119== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==17119== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==17119== Command: RunCollatz
==17119==
==17119==
==17119== HEAP SUMMARY:
==17119==     in use at exit: 0 bytes in 0 blocks
==17119==   total heap usage: 2 allocs, 2 frees, 1,136 bytes allocated
==17119==
==17119== All heap blocks were freed -- no leaks are possible
==17119==
==17119== For counts of detected and suppressed errors, rerun with: -v
==17119== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)



% gcov-4.7 -b Collatz.c++
File 'Collatz.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Collatz.c++.gcov'
...



% cat Collatz.c++.gcov
...



% gcov-4.7 -b RunCollatz.c++
File 'RunCollatz.c++'
Lines executed:100.00% of 3
Branches executed:100.00% of 4
Taken at least once:50.00% of 4
Calls executed:100.00% of 2
Creating 'RunCollatz.c++.gcov'
...



% cat RunCollatz.c++.gcov
...
*/

        
