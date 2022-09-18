
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "cmdln/flags.h"
#include "cmdln/process.h"
#include "cmdln/free.h"

#include "parse/mains.h"

int main(int argc, char* const* argv)
{
	ENTER;
	
	struct cmdln* flags = cmdln_process(argc, argv);
	
	TODO;
	#if 0
	struct avl_tree* grammar = avl_alloc_tree(compare_named_grammars, free_named_grammar);
	
	struct expressionset* assertions = new_expressionset();
	
	mains_parse(flags->input_path);
	
	// scope:
		// needs push, pop, declare, lookup functions.
		// also saves named_gegexes
	
	// parse
		// grammar declarations:
			// regular expressions:
				// parse as NFA
				// convert to DFA and simplifiy at the end
				// get token id from lexer
			// token transitions:
				// tokens have a type: boolean, integer, string
				// include in gegex's transition's structinfo
			// grammar transitions:
				// we may not have read this grammar yet, but we still know the
				// datatype
			// parse grammar as NFA
			// build big structinfo
			// generate grammar datatype,
			// declare type into scope
			// declared named grammar into scope
		// defines:
			// parse expression
			// evaluate now
			// save result to scope
		// assertions
			// read as a parse-tree-expression
				// any lambdas you find, should be added to the lambda todo list
			// add to list
	
	// list for converted assertions
	
	// tree of converted lambdas (original) -> specialized
	
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
	#endif
	
	free_cmdln(flags);
	
	EXIT;
	return 0;
}















