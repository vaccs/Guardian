
#include <debug.h>

#include <quack/new.h>
#include <quack/free.h>

#include <assertion/print_source.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>

#include "out.h"

struct stringtree* out(
	struct ptrset* assertions)
{
	ENTER;
	
	struct stringtree* root = new_stringtree();
	
	struct quack* types = new_quack();
	
	struct quack* declares = new_quack();
	
	stringtree_append_printf(root, "int main() {");
	
	ptrset_foreach(assertions, ({
		void runme(void* ptr)
		{
			ENTER;
			
			struct stringtree* sub = assertion_print_source(ptr);
			
			stringtree_append_tree(root, sub);
			
			EXIT;
		}
		runme;
	}));
	
	stringtree_append_printf(root, "}");
	
	free_quack(declares);
	
	free_quack(types);
	
	EXIT;
	return root;
}

	// generate output (in some kind of string-builder data structure):
		// needs some kind of variable-name generator to be passed around
		
		// start with the assertions:
			// generate their source code
			// based on what they need:
				// add used types to type source-generation queue
				// add used declares to value-declare source-generation queue
		
		// for all declares:
			// (prepend) their generated source code
			// based on what they need:
				// add used types to type source-generation queue
				// add used declares to value-declare source-generation queue
		
		// generate source code for parser:
			// create sets for each kind of grammar-rule
			// insert code for reduction rules
		
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
	
