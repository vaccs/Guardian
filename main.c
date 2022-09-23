
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <cmdln/flags.h>
#include <cmdln/process.h>
#include <cmdln/free.h>

#include <parse/driver.h>

#include <named/grammar/compare.h>
#include <named/grammar/free.h>

#include <named/type/compare.h>
#include <named/type/free.h>

#include <named/zebu_expression/compare.h>
#include <named/zebu_expression/free.h>

#include <set/ptr/new.h>

#include <lex/new.h>
#include <lex/free.h>

#include <type_cache/new.h>

int main(int argc, char* const* argv)
{
	#ifdef DEBUGGING
	setvbuf(stdout, NULL, 0, _IONBF);
	setvbuf(stderr, NULL, 0, _IONBF);
	#endif
	ENTER;
	
	struct cmdln* flags = cmdln_process(argc, argv);
	
	struct lex* lex = new_lex();
	
	struct avl_tree_t* grammar = avl_alloc_tree(compare_named_grammars, free_named_grammar);
	
	struct avl_tree_t* types = avl_alloc_tree(compare_named_types, free_named_type);
	
	struct avl_tree_t* declares = avl_alloc_tree(compare_named_zebu_expressions, free_named_zebu_expression);
	
	struct ptrset* assertions = new_ptrset();
	
	struct type_cache* tcache = new_type_cache();
	
	parse_driver(lex, grammar, types, declares, assertions, tcache, flags->input_path);
	
	TODO;
	#if 0
	
	// traverse through parse-tree:
		// regular expressions:
			// build NFA
			// convert to DFA and simplifiy at the end
			// get token id from lexer
		// grammar rules:
			// build NFA
			// parse grammar as NFA
			// build big structinfo
			// generate grammar datatype,
			// declare type into scope
			// declared named grammar into scope
	
	// process lambda-captures/variable references:
		// gives each parse-tree variable-use a type, maybe even a value
	
	// type-check/specialize expressions
		// will create new expression structs with types
	
	// generate parser
	
	// print source for parser
	
	// print source for assertions:
		// boolean, integers, and string types become `bool` , `int`, and `string`
		
		// lists become a typed-pointer with a reference-count
		// lambdas become a struct:
			// with a reference-count
			// with a function-pointer
			// and a struct of "captured" values
			// first parameter of function-pointer is the struct
		
		// iterate through assertions, generating their code.
			// for every global value or named-lambda that' used, add them to
			// the todo for code generation, their code will be prepended.
			// for any structs that are used, add the, to todo, their code will
			// be prepended before both.
			
			// in the file:
				// 0. structs
				// 1. parsing and set-building
				// 2. globals and lambdas
				// 3. assertions
		
	
	avl_free_tree(grammar);
	
	free_expressionset(assertions);
	
	free_type_cache(tcache);
	
	#endif
	
	free_lex(lex);
	
	free_cmdln(flags);
	
	EXIT;
	return 0;
}















