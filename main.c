
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <cmdln/flags.h>
#include <cmdln/process.h>
#include <cmdln/free.h>

#include <parse/driver.h>

#include <parse/assertion/free.h>
#include <assertion/free.h>

#include <named/grammar/compare.h>
#include <named/grammar/free.h>

#include <named/type/compare.h>
#include <named/type/free.h>

#include <named/zebu_expression/compare.h>
#include <named/zebu_expression/free.h>

#include <named/expression/compare.h>
#include <named/expression/free.h>

#include <set/ptr/new.h>

#include <lex/new.h>
#include <lex/free.h>

#include <type_cache/new.h>
#include <type_cache/free.h>

#include <type_check/type_check.h>

#include <yacc/yacc.h>

#include <yacc/state/free.h>

int main(int argc, char* const* argv)
{
	#ifdef DEBUGGING
/*	setvbuf(stdout, NULL, 0, _IONBF);*/
/*	setvbuf(stderr, NULL, 0, _IONBF);*/
	#endif
	
	ENTER;
	
	struct cmdln* flags = cmdln_process(argc, argv);
	
	struct lex* lex = new_lex();
	
	struct type_cache* tcache = new_type_cache();
	
	struct ptrset* raw_assertions = new_ptrset();
	
	struct avl_tree_t* grammar = avl_alloc_tree(compare_named_grammars, free_named_grammar);
	
	struct avl_tree_t* types = avl_alloc_tree(compare_named_types, free_named_type);
	
	struct avl_tree_t* raw_declares = avl_alloc_tree(compare_named_zebu_expressions, free_named_zebu_expression);
	
	parse_driver(lex, grammar, types, raw_declares, raw_assertions, tcache, flags->input_path);
	
	struct ptrset* typed_assertions = new_ptrset();
	
	struct avl_tree_t* typed_declares = avl_alloc_tree(compare_named_expressions, free_named_expression);
	
	type_check(tcache, types, typed_declares, typed_assertions, raw_declares, raw_assertions);
	
	struct yacc_state* start = yacc(lex, grammar);
	
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
	
	ptrset_foreach(raw_assertions, ({
		void runme(void* ptr) {
			free_raw_assertion(ptr);
		}
		runme;
	}));
	
	ptrset_foreach(typed_assertions, ({
		void runme(void* ptr) {
			free_assertion(ptr);
		}
		runme;
	}));
	
	free_yacc_state(start);
	
	free_ptrset(raw_assertions);
	
	free_ptrset(typed_assertions);
	
	avl_free_tree(typed_declares);
	
	avl_free_tree(raw_declares);
	
	free_type_cache(tcache);
	
	avl_free_tree(grammar);
	
	avl_free_tree(types);
	
	free_cmdln(flags);
	
	free_lex(lex);
	
	EXIT;
	return 0;
}















