
#include <debug.h>

/*#include <quack/new.h>*/
#include <quack/foreach.h>
/*#include <quack/free.h>*/

/*#include <set/string/new.h>*/
/*#include <set/string/free.h>*/

#include <lex/state/struct.h>

#include <yacc/state/struct.h>

#include <assertion/print_source.h>

#include "ystate_to_id/new.h"
#include "ystate_to_id/ystate_to_id.h"

#include "lstate_to_id/new.h"
#include "lstate_to_id/lstate_to_id.h"

#include "unsignedset_to_id/new.h"
#include "unsignedset_to_id/unsignedset_to_id.h"

#include "string_to_id/new.h"
#include "string_to_id/string_to_id.h"

#include "reducerule_to_id/new.h"
#include "reducerule_to_id/reducerule_to_id.h"

#include "dynvector/new.h"
#include "dynvector/set.h"

#include "dyntable/new.h"
#include "dyntable/set.h"

#include "declare_queue/struct.h"
#include "declare_queue/new.h"
#include "declare_queue/process.h"
#include "declare_queue/free.h"

#include "set_queue/struct.h"
#include "set_queue/new.h"
#include "set_queue/process.h"
#include "set_queue/free.h"

#include "function_queue/struct.h"
#include "function_queue/new.h"
#include "function_queue/process.h"
#include "function_queue/free.h"

#include "type_queue/struct.h"
#include "type_queue/new.h"
#include "type_queue/process.h"
#include "type_queue/free.h"

#include "shared.h"
#include "escaped.h"
#include "out.h"

struct stringtree* out(
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct avl_tree_t* declares,
	struct quack* assertions,
	struct yacc_state* yacc_start)
{
	ENTER;
	
	struct ystate_to_id* ytoi = new_ystate_to_id();
	
	struct lstate_to_id* ltoi = new_lstate_to_id();
	
	struct unsignedset_to_id* ustoi = new_unsignedset_to_id();
	
	struct string_to_id* stoi = new_string_to_id();
	
	struct reducerule_to_id* rrtoi = new_reducerule_to_id();
	
	struct dyntable*  lexer   = new_dyntable("lexer_transitions");
	struct dynvector* starts  = new_dynvector("lexer_starts");
	struct dynvector* accepts = new_dynvector("lexer_accepts");
	struct dynvector* EOFs    = new_dynvector("lexer_EOFs");
	
	struct dyntable* shifts  = new_dyntable("shifts");
	struct dyntable* reduces = new_dyntable("reduces");
	struct dyntable* gotos   = new_dyntable("gotos");
	
	struct quack* yacc_todo = new_quack();
	struct quack* lex_todo = new_quack();
	
	struct ptrset* yacc_queued = new_ptrset();
	struct ptrset* lex_queued = new_ptrset();
	
	ptrset_add(yacc_queued, yacc_start);
	quack_append(yacc_todo, yacc_start);
	
	while (quack_is_nonempty(yacc_todo))
	{
		struct yacc_state* const state = quack_pop(yacc_todo);
		
		unsigned yid = ystate_to_id(ytoi, state);
		
		dpv(yid);
		
		// tokenizer:
		{
			struct lex_state* lstate = state->tokenizer_start;
			
			unsigned lid = lstate_to_id(ltoi, lstate);
			
			dpv(lid);
			
			if (ptrset_add(lex_queued, lstate))
				quack_append(lex_todo, lstate);
			
			dynvector_set(starts, yid, lid);
		}
		
		// shift transitions:
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct yacc_state_transition* const ele = state->transitions.data[i];
			
			unsigned tid = unsignedset_to_id(ustoi, ele->on);
			
			unsigned syid = ystate_to_id(ytoi, ele->to);
			
			dyntable_set(shifts, yid, tid, syid);
			
			if (ptrset_add(yacc_queued, ele->to))
				quack_append(yacc_todo, ele->to);
		}
		
		// grammar transitions:
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct yacc_state_grammar_transition* const ele = state->grammar_transitions.data[i];
			
			dpvs(ele->grammar);
			
			unsigned gid = string_to_id(stoi, ele->grammar);
			
			unsigned syid = ystate_to_id(ytoi, ele->to);
			
			dyntable_set(gotos, yid, gid, syid);
			
			if (ptrset_add(yacc_queued, ele->to))
				quack_append(yacc_todo, ele->to);
		}
		
		// reduce transitions:
		for (unsigned i = 0, n = state->reduce_transitions.n; i < n; i++)
		{
			struct yacc_state_reduce_transition* const ele = state->reduce_transitions.data[i];
			
			unsigned tid = unsignedset_to_id(ustoi, ele->on);
			
			unsigned rrid = reducerule_to_id(rrtoi, ele->reduce_as, ele->grammar, ele->reductioninfo, ele->structinfo);
			
			dyntable_set(reduces, yid, tid, rrid);
		}
	}
	
	while (quack_is_nonempty(lex_todo))
	{
		struct lex_state* const state = quack_pop(lex_todo);
		
		unsigned lid = lstate_to_id(ltoi, state);
		
		dpv(lid);
		
		if (state->accepts)
		{
			if (state->kind == tk_whitespace)
			{
				dynvector_set(accepts, lid, 1);
			}
			else
			{
				unsigned tid = unsignedset_to_id(ustoi, state->accepts);
				
				dpv(tid);
				
				dynvector_set(accepts, lid, tid);
			}
		}
		
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct lex_state* to = state->transitions[i];
			
			if (to)
			{
				unsigned slid = lstate_to_id(ltoi, to);
				
				dyntable_set(lexer, lid, i, slid);
				
				if (ptrset_add(lex_queued, to))
					quack_append(lex_todo, to);
			}
		}
		
		if (state->EOF_transition_to)
		{
			struct lex_state* to = state->EOF_transition_to;
			
			unsigned slid = lstate_to_id(ltoi, to);
			
			dynvector_set(EOFs, lid, slid);
			
			if (ptrset_add(lex_queued, to))
				quack_append(lex_todo, to);
		}
	}
	
	struct out_shared shared;
	
	shared.tqueue = new_type_queue();
	
	shared.fqueue = new_function_queue();
	
	shared.squeue = new_set_queue();
	
	shared.dqueue = new_declare_queue();
	
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
	
	declare_queue_process(shared.dqueue, declares, &shared);
	
	set_queue_process(shared.squeue, tcache, grammar_types, &shared);
	
	#if 0
	struct stringtree* reduction_rules_text = new_stringtree();
	
	// generate reduction-rule text
	// if grammar name is in list of needed sets, add code for appending to
		// set-list
	TODO;
	#endif
	
	function_queue_process(shared.fqueue);
	
	type_queue_process(shared.tqueue);
	
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
			else if (!strncmp(old, "LEXER_TRANSITION_TABLE", len))
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
			else if (!strncmp(old, "STRUCTS", len))
			{
				stringtree_append_tree(root, shared.tqueue->text);
			}
			else if (!strncmp(old, "FUNCTIONS", len))
			{
				stringtree_append_tree(root, shared.fqueue->text);
			}
			else if (!strncmp(old, "INIT_DECLARES", len))
			{
				stringtree_append_tree(root, shared.dqueue->init_text);
			}
			else if (!strncmp(old, "UNINIT_DECLARES", len))
			{
				stringtree_append_tree(root, shared.dqueue->uninit_text);
			}
			else if (!strncmp(old, "INIT_SETS", len))
			{
				stringtree_append_tree(root, shared.squeue->init_text);
			}
			else if (!strncmp(old, "UNINIT_SETS", len))
			{
				stringtree_append_tree(root, shared.squeue->uninit_text);
			}
			else if (!strncmp(old, "ASSERTIONS", len))
			{
				stringtree_append_tree(root, assertions_text);
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
	
	free_type_queue(shared.tqueue);
	
	free_function_queue(shared.fqueue);
	
	free_set_queue(shared.squeue);
	
	free_declare_queue(shared.dqueue);
	
	free_stringtree(assertions_text);
	
	TODO;
	#if 0
	free_reducerule_to_id(rrtoi);
	
	free_unsignedset_to_id(ustoi);
	
	free_ptrset(yacc_queued);
	
	free_ptrset(lex_queued);
	
	free_string_to_id(stoi);
	
	free_ystate_to_id(ytoi);
	
	free_lstate_to_id(ltoi);
	
	free_dynvector(starts);
	free_dynvector(EOFs);
	free_dynvector(accepts);
	
	free_dyntable(lexer);
	free_dyntable(shifts);
	free_dyntable(reduces);
	free_dyntable(gotos);
	
	free_quack(yacc_todo);
	free_quack(lex_todo);
	#endif
	
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
	
