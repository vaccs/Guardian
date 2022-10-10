
#include <debug.h>

#include <quack/new.h>
#include <quack/foreach.h>
#include <quack/free.h>

#include <set/string/new.h>
#include <set/string/free.h>

#include <assertion/print_source.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_strndup.h>
#include <stringtree/free.h>

#include <named/expression/struct.h>

#include <expression/struct.h>
#include <expression/print_source.h>

#include <named/type/struct.h>

#include <type/struct.h>
#include <type/free.h>

#include <type_cache/get_type/list.h>

#include "type_lookup/new.h"
#include "type_lookup/lookup.h"
#include "type_lookup/calc_rank.h"
#include "type_lookup/free.h"

#include "function_lookup/new.h"
#include "function_lookup/lookup_new.h"
#include "function_lookup/lookup_free.h"
#include "function_lookup/calc_rank.h"
#include "function_lookup/free.h"

#include "type/struct.h"

#include "shared.h"
#include "escaped.h"
#include "out.h"

struct stringtree* out(
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct avl_tree_t* typed_declares,
	struct quack* assertions)
{
	ENTER;
	
	struct out_shared shared;
	
	shared.declares.todo = new_quack(); // list of names
	shared.declares.queued = new_stringset();
	
	shared.sets.todo = new_quack(); // list of names
	shared.sets.queued = new_stringset();
	
	shared.tlookup = new_type_lookup();
	
	shared.flookup = new_function_lookup();
	
	struct stringtree* assertions_text = new_stringtree();
	
	quack_foreach(assertions, ({
		void runme(void* ptr)
		{
			struct assertion* assertion = ptr;
			
			struct stringtree* text = assertion_print_source(assertion, &shared);
			
			stringtree_append_tree(assertions_text, text);
			
			free_stringtree(text);
		}
		runme;
	}));
	
	struct stringtree* init_declares_text = new_stringtree();
	
	struct stringtree* uninit_declares_text = new_stringtree();
	
	while (quack_is_nonempty(shared.declares.todo))
	{
		struct string* name = quack_pop(shared.declares.todo);
		
		struct avl_node_t* node = avl_search(typed_declares, &name);
		
		assert(node);
		
		struct named_expression* nexpression = node->item;
		
		struct expression* expression = nexpression->expression;
		
		struct type* type = expression->type;
		
		type_lookup(shared.tlookup, type, NULL);
		
		unsigned type_id = type->id;
		
		stringtree_append_printf(init_declares_text, ""
			"type_%u* %.*s = "
		"", type_id, name->len, name->chars);
		
		struct stringtree* text = expression_print_source(expression, &shared);
		
		stringtree_append_tree(init_declares_text, text);
		
		stringtree_append_printf(init_declares_text, ""
			";"
		"");
		
		TODO;
		#if 0
		unsigned free_id = function_lookup_free(shared.flookup, type);
		
		stringtree_append_printf(uninit_declares_text, ""
			"func_%u(%.*s);"
		"", free_id, name->len, name->chars);
		#endif
		
		free_stringtree(text);
	}
	
	#if 0
	struct stringtree* shift_table_text = new_stringtree();
	struct stringtree* reduce_table_text = new_stringtree();
	struct stringtree* goto_table_text = new_stringtree();
	struct stringtree* lexer_table_text = new_stringtree();
	
	// generate parse table text
	TODO;
	#endif
	
	struct stringtree* init_sets_text = new_stringtree();
	struct stringtree* uninit_sets_text = new_stringtree();
	
	// generate text for declaring lists of grammar data
	while (quack_is_nonempty(shared.sets.todo))
	{
		struct string* name = quack_pop(shared.sets.todo);
		
		struct avl_node_t* node = avl_search(grammar_types, &name);
		
		assert(node);
		
		struct named_type* ntype = node->item;
		
		struct type* type = ntype->type;
		
		struct type* ltype = type_cache_get_list_type(tcache, type);
		
		type_lookup(shared.tlookup, ltype, NULL);
		
		unsigned new_id = function_lookup_new(shared.flookup, ltype);
		
		TODO;
		#if 0
		unsigned free_id = function_lookup_free(shared.flookup, ltype);
		
		stringtree_append_printf(init_sets_text, ""
			"type_%u* %.*s_set = func_%u();"
		"", ltype->id, name->len, name->chars, new_id);
		
		stringtree_append_printf(uninit_sets_text, ""
			"func_%u(%.*s_set);"
		"", free_id, name->len, name->chars);
		
		free_type(ltype);
		#endif
	}
	
	#if 0
	struct stringtree* reduction_rules_text = new_stringtree();
	
	// generate reduction-rule text
	// if grammar name is in list of needed sets, add code for appending to
		// set-list
	TODO;
	#endif
	
	struct heap* type_heap = type_lookup_calc_rank(shared.tlookup);
	
	struct heap* function_heap = function_lookup_calc_rank(shared.flookup);
	
	struct stringtree* root = new_stringtree();
	
	{
		const char* last = template, *moving, *end = template + strlen(template);
		
		while ((moving = strstr(last, "{{")))
		{
			stringtree_append_strndup(root, last, moving - last), moving += 2;
			
			const char* old = moving;
			
			moving = strstr(moving, "}}");
			
			unsigned len = moving - old;
			
			if (!strncmp(old, "SHIFT_TABLE", len))
			{
				TODO;
				#if 0
				dyntable_print_source(shifts, output_prefix, stream);
				#endif
			}
			else if (!strncmp(old, "REDUCE_TABLE", len))
			{
				TODO;
/*				dyntable_print_source(reduces, output_prefix, stream);*/
			}
			else if (!strncmp(old, "GOTO_TABLE", len))
			{
				TODO;
/*				dyntable_print_source(gotos, output_prefix, stream);*/
			}
			else if (!strncmp(old, "LEXER_TABLE", len))
			{
				TODO;
/*				dyntable_print_source(lexer, output_prefix, stream);*/
			}
			else if (!strncmp(old, "LEXER_STARTS_TABLE", len))
			{
				TODO;
/*				dynvector_print_source(starts, output_prefix, stream);*/
			}
			else if (!strncmp(old, "LEXER_ACCEPTS_TABLE", len))
			{
				TODO;
/*				dynvector_print_source(accepts, output_prefix, stream);*/
			}
			else if (!strncmp(old, "LEXER_EOF_TABLE", len))
			{
				TODO;
/*				dynvector_print_source(EOFs, output_prefix, stream);*/
			}
			else if (!strncmp(old, "STRUCTS", len))
			{
				while (heap_is_nonempty(type_heap))
				{
					struct out_type* otype = heap_pop(type_heap);
					stringtree_append_tree(root, otype->text);
				}
			}
			else if (!strncmp(old, "TYPE_FUNCTIONS", len))
			{
				while (heap_is_nonempty(function_heap))
				{
					struct out_type* otype = heap_pop(function_heap);
					stringtree_append_tree(root, otype->text);
				}
			}
			else if (!strncmp(old, "START_GRAMMAR_ID", len))
			{
				TODO;
/*				struct string* start = new_string("$start");*/
/*				fprintf(stream, "%u", string_to_id(stoi, start));*/
/*				free_string(start);*/
			}
			else if (!strncmp(old, "REDUCTION_RULE_SWITCH", len))
			{
				TODO;
/*				reducerule_to_id_print_source(rrtoi, stoi, output_prefix, stream);*/
			}
			else
			{
				dpvsn(old, len);
				TODO;
			}
			
			last = moving + 2;
		}
		
		stringtree_append_strndup(root, last, end - last);
	}
	
	free_heap(type_heap);
	
	free_heap(function_heap);
	
	free_stringtree(assertions_text);
	
	free_stringtree(init_declares_text);
	free_stringtree(uninit_declares_text);
	
	free_stringtree(init_sets_text);
	free_stringtree(uninit_sets_text);
	
	free_quack(shared.declares.todo);
	free_stringset(shared.declares.queued);
	
	free_quack(shared.sets.todo);
	free_stringset(shared.sets.queued);
	
	free_type_lookup(shared.tlookup);
	
	free_function_lookup(shared.flookup);
	
	EXIT;
	return root;
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
	
