
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "out.h"

struct stringtree* out()
{
	ENTER;
	
	struct stringtree* retval = new_stringtree();
	
	stringtree_append_printf(retval, "hello world!\n");
	
	EXIT;
	return retval;
}

	// generate output (in some kind of string-builder data structure):
		// needs some kind of variable-name generator to be passed around
		
		// start with the assertions:
			// generate their source code
			// based on what they need:
				// add used types to type source-generation queue
				// add used declares to value-declare source-generation queue
				// "mark"? grammar sets as being used.
		
		// for all declares:
			// (prepend) their generated source code
			// based on what they need:
				// add used types to type source-generation queue
				// add used declares to value-declare source-generation queue
				// "mark"? grammar sets as being used.
		
		// generate source code for parser:
			// for all of the "marked" grammar-rules, create lists for their
				// values
			// keep all of the reduction-rules for building the structs
			// insert code in reduction-rules for appending structs to their
				// lists
		
		// for all types:
			// (prepend) their generated source code
			// based on what they need:
				// add used types to type source-generation queue
			
	
	
	#if 0
	// print source for all types
	
	// print source for parser and set-building
	
	// print source for value-declares
	
	// boolean, integers, float, and char types become `bool`, `float`, `int`, and `char`
	
	// lists become a typed-pointer with a reference-count
	// lambdas become a struct:
		// with a reference-count
		// with a function-pointer
		// and a struct of "captured" values
		// first parameter of function-pointer is the struct
	
	// if other code-generating stuff sees its invoking a lambda literal
	// the lambda can be inlined.
	
	// iterate through assertions, generating their code.
		// for every global value or named-lambda that' used, add them to
		// the todo for code generation, their code will be prepended.
		// for any structs that are used, add the to todo, their code will
		// be prepended before both.
		
		// in the file:
			// 0. structs
			// 1. parsing and set-building
			// 2. globals and lambdas
			// 3. assertions
	#endif
	
