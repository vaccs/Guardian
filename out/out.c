
#include <debug.h>

#include <quack/new.h>
#include <quack/foreach.h>
#include <quack/free.h>

#include <set/string/new.h>

#include <assertion/print_source.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>

#include <named/expression/struct.h>

#include <expression/struct.h>
#include <expression/print_source.h>

#include <type/struct.h>

#include "type_lookup/new.h"
#include "type_lookup/lookup.h"

#include "function_lookup/new.h"
#include "function_lookup/lookup_free.h"

#include "shared.h"
#include "out.h"

struct stringtree* out(
	struct avl_tree_t* typed_declares,
	struct quack* assertions)
{
	ENTER;
	
	struct out_shared shared;
	
	shared.declare.todo = new_quack(); // list of names
	shared.declare.queued = new_stringset();
	
	shared.set.todo = new_quack(); // list of names
	shared.set.queued = new_stringset();
	
	shared.tlookup = new_type_lookup();
	
	shared.flookup = new_function_lookup();
	
	struct stringtree* assertions_text = new_stringtree();
	
	quack_foreach(assertions, ({
		void runme(void* ptr)
		{
			struct assertion* assertion = ptr;
			
			struct stringtree* text = assertion_print_source(assertion, &shared);
			
			stringtree_append_tree(assertions_text, text);
		}
		runme;
	}));
	
	struct stringtree* init_declares_text = new_stringtree();
	
	struct stringtree* uninit_declares_text = new_stringtree();
	
	while (quack_is_nonempty(shared.declare.todo))
	{
		struct string* name = quack_pop(shared.declare.todo);
		
		struct avl_node_t* node = avl_search(typed_declares, &name);
		
		assert(node);
		
		struct named_expression* nexpression = node->item;
		
		struct expression* expression = nexpression->expression;
		
		struct type* type = expression->type;
		
		type_lookup(shared.tlookup, type);
		
		unsigned type_id = type->id;
		
		stringtree_append_printf(init_declares_text, ""
			"type_%u* %.*s = "
		"", type_id, name->len, name->chars);
		
		stringtree_append_tree(init_declares_text, expression_print_source(expression, &shared));
		
		stringtree_append_printf(init_declares_text, ""
			";"
		"");
		
		unsigned free_id = function_lookup_free(shared.flookup, type);
		
		stringtree_append_printf(uninit_declares_text, ""
			"func_%u(%.*s);"
		"", free_id, name->len, name->chars);
	}
	
	TODO;
	#if 0
	struct stringtree* shift_table_text = new_stringtree();
	struct stringtree* reduce_table_text = new_stringtree();
	struct stringtree* goto_table_text = new_stringtree();
	struct stringtree* lexer_table_text = new_stringtree();
	
	// generate parse table text
	TODO;
	
	struct stringtree* sets_text = new_stringtree();
	
	// generate text for declaring lists of grammar data
	TODO;
	
	struct stringtree* reduction_rules_text = new_stringtree();
	
	// generate reduction-rule text
	// if grammar name is in list of needed sets, add code for appending to
		// set-list
	TODO;
	
	struct stringtree* supports_text = new_stringtree();
	
	struct quack* all_types = new_quack();
	struct quack* all_functions = new_quack();
	// determine order of structs' and functions' text
	TODO;
	
	struct stringtree* root = new_stringtree();
	
	// use find-and-replace template from zebu
	// TODO;
	
	EXIT;
	return root;
	#endif
}

#if 0

	ptrset_foreach(assertions, ({
		void runme(void* ptr)
		{
			ENTER;
			
			struct stringtree* sub = assertion_print_source(ptr, shared);
			
			stringtree_append_tree(root, sub);
			
			EXIT;
		}
		runme;
	}));
	#endif

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
	
