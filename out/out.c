
#include <assert.h>

#include <string.h>

#include <debug.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/foreach.h>
#include <avl/free_tree.h>

#include <quack/new.h>
#include <quack/foreach.h>
/*#include <quack/free.h>*/

/*#include <set/string/new.h>*/
/*#include <set/string/free.h>*/

#include <set/ptr/new.h>
#include <set/ptr/add.h>

#include <string/struct.h>

#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <string/new.h>
#include <string/free.h>

#include <statement/struct.h>

#include <list/statement/foreach.h>

#include <expression/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_strndup.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <set/ptr/free.h>

#include <lex/state/struct.h>

#include <yacc/state/struct.h>

/*#include <assertion/print_source.h>*/

#include <named/type/struct.h>

#include <type/struct.h>

#include <type/environment/struct.h>

#include <type_cache/get_environment_type.h>
#include <type_cache/get_list_type.h>

#include <expression/print_source.h>

/*#include <list/assertion/foreach.h>*/

/*#include <declaration/struct.h>*/

/*#include <list/declaration/foreach.h>*/

#include <named/type/new.h>
#include <named/type/compare.h>
#include <named/type/free.h>

#include "ystate_to_id/new.h"
#include "ystate_to_id/ystate_to_id.h"
#include "ystate_to_id/free.h"

#include "lstate_to_id/new.h"
#include "lstate_to_id/lstate_to_id.h"
#include "lstate_to_id/free.h"

#include "unsignedset_to_id/new.h"
#include "unsignedset_to_id/unsignedset_to_id.h"
#include "unsignedset_to_id/free.h"

#include "string_to_id/new.h"
#include "string_to_id/string_to_id.h"
#include "string_to_id/free.h"

#include "reducerule_to_id/new.h"
#include "reducerule_to_id/reducerule_to_id.h"
#include "reducerule_to_id/print_source.h"
#include "reducerule_to_id/free.h"

#include <statement/print_source.h>

#include "dynvector/new.h"
#include "dynvector/print_source.h"
#include "dynvector/set.h"
#include "dynvector/free.h"

#include "dyntable/new.h"
#include "dyntable/print_source.h"
#include "dyntable/set.h"
#include "dyntable/free.h"

/*#include "declare_queue/struct.h"*/
/*#include "declare_queue/new.h"*/
/*#include "declare_queue/process.h"*/
/*#include "declare_queue/free.h"*/

/*#include "set_queue/struct.h"*/
/*#include "set_queue/new.h"*/
/*#include "set_queue/process.h"*/
/*#include "set_queue/free.h"*/

#include "function_queue/struct.h"
#include "function_queue/new.h"
#include "function_queue/submit_new.h"
#include "function_queue/submit_print.h"
#include "function_queue/submit_free.h"
#include "function_queue/process.h"
#include "function_queue/free.h"

#include "subtype_queue/struct.h"
#include "subtype_queue/new.h"
#include "subtype_queue/process.h"
#include "subtype_queue/free.h"

#include "type_queue/struct.h"
#include "type_queue/new.h"
#include "type_queue/submit.h"
#include "type_queue/process.h"
#include "type_queue/free.h"

#include <list/statement/foreach.h>

#include <statement/struct.h>
#include <statement/declare/struct.h>
#include <statement/parse/struct.h>

#include "shared.h"
#include "escaped.h"
#include "out.h"

struct stringtree* out(
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct statement_list* statements)
{
	ENTER;
	
	struct ystate_to_id* ytoi = new_ystate_to_id();
	
	struct lstate_to_id* ltoi = new_lstate_to_id();
	
	struct unsignedset_to_id* ustoi = new_unsignedset_to_id();
	
	struct string_to_id* stoi = new_string_to_id();
	
	struct reducerule_to_id* rrtoi = new_reducerule_to_id();
	
	struct dyntable*  lexer   = new_dyntable ("lexer_transitions");
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
	
	statement_list_foreach(statements, ({
		void runme(struct statement* statement)
		{
			if (statement->kind == sk_parse)
			{
				struct parse_statement* pstatement = (void*) statement;
				
				struct yacc_state* ystate = pstatement->ystate;
				
				ptrset_add(yacc_queued, ystate);
				
				quack_append(yacc_todo, ystate);
				
				pstatement->start_id = ystate_to_id(ytoi, ystate);
				
				pstatement->grammar_id = string_to_id(stoi, pstatement->grammar_name);
			}
		}
		runme;
	}));
	
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
		
		dpvb(state->accepts);
		
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
				dpv(to);
				
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
	
	shared.tcache = tcache;
	
	shared.tqueue = new_type_queue();
	
	shared.stqueue = new_subtype_queue();
	
	shared.fqueue = new_function_queue();
	
	struct type* environment_type;
	struct stringtree* declare_environment_text = new_stringtree();
	struct stringtree* assign_environment_text = new_stringtree();
	struct stringtree* free_environment_text = new_stringtree();
	{
		struct avl_tree_t* environment_tree =
			avl_alloc_tree(compare_named_types, free_named_type);
		
		avl_foreach(grammar_types, ({
			void runme(void *ptr)
			{
				struct named_type* ntype = ptr;
				
				struct type* ltype = type_cache_get_list_type(tcache, ntype->type);
				
				struct named_type* new = new_named_type(ntype->name, ltype);
				
				void* ptr2 = avl_insert(environment_tree, new);
				
				assert(ptr2);
			}
			runme;
		}));
		
		statement_list_foreach(statements, ({
			void runme(struct statement* statement)
			{
				if (statement->kind == sk_declare)
				{
					struct declare_statement* dstatement = (void*) statement;
					
					struct named_type* new = new_named_type(dstatement->name, dstatement->expression->type);
					
					void* ptr2 = avl_insert(environment_tree, new);
					
					assert(ptr2);
				}
			}
			runme;
		}));
		
		environment_type = type_cache_get_environment_type2(tcache, NULL, environment_tree);
		
		stringtree_append_printf(declare_environment_text, ""
			"struct type_%u* environment = NULL;"
		"", environment_type->id);
		
		unsigned new_id = function_queue_submit_new(shared.fqueue, environment_type);
		
		stringtree_append_printf(assign_environment_text, ""
			"environment = func_%u();"
		"", new_id);
		
		unsigned free_id = function_queue_submit_free(shared.fqueue, environment_type);
		
		stringtree_append_printf(free_environment_text, ""
			"func_%u(environment);"
		"", free_id);
		
		avl_free_tree(environment_tree);
	}
	type_queue_submit(shared.tqueue, environment_type);
	
	struct stringtree* assign_sets_text = new_stringtree();
	{
		avl_foreach(grammar_types, ({
			void runme(void* ptr)
			{
				struct named_type* ntype = ptr;
				
				struct type* type = ntype->type;
				
				struct type* ltype = type_cache_get_list_type(tcache, type);
				
				unsigned new_id = function_queue_submit_new(shared.fqueue, ltype);
				
				stringtree_append_printf(assign_sets_text, ""
					"environment->$%.*s = func_%u();"
				"", ntype->name->len, ntype->name->chars, new_id);
			}
			runme;
		}));
	}
	
	struct stringtree* statements_text = new_stringtree();
	statement_list_foreach(statements, ({
		void runme(struct statement* statement)
		{
			struct stringtree* tree = statement_print_source(
				statement, &shared, environment_type);
			
			stringtree_append_tree(statements_text, tree);
			
			free_stringtree(tree);
		}
		runme;
	}));
	
	struct stringtree* reductionrules_text =
		reducerule_to_id_print_source(rrtoi, stoi, &shared);
	
	function_queue_process(shared.fqueue, &shared);
	
	subtype_queue_process(shared.stqueue, shared.tqueue);
	
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
				struct stringtree* text = dyntable_print_source(shifts);
				stringtree_append_tree(root, text);
				free_stringtree(text);
			}
			else if (!strncmp(old, "REDUCE_TABLE", len))
			{
				struct stringtree* text = dyntable_print_source(reduces);
				stringtree_append_tree(root, text);
				free_stringtree(text);
			}
			else if (!strncmp(old, "GOTO_TABLE", len))
			{
				struct stringtree* text = dyntable_print_source(gotos);
				stringtree_append_tree(root, text);
				free_stringtree(text);
			}
			else if (!strncmp(old, "LEXER_TRANSITION_TABLE", len))
			{
				struct stringtree* text = dyntable_print_source(lexer);
				stringtree_append_tree(root, text);
				free_stringtree(text);
			}
			else if (!strncmp(old, "LEXER_STARTS", len))
			{
				struct stringtree* text = dynvector_print_source(starts);
				stringtree_append_tree(root, text);
				free_stringtree(text);
			}
			else if (!strncmp(old, "LEXER_ACCEPTS", len))
			{
				struct stringtree* text = dynvector_print_source(accepts);
				stringtree_append_tree(root, text);
				free_stringtree(text);
			}
			else if (!strncmp(old, "LEXER_EOFS", len))
			{
				struct stringtree* text = dynvector_print_source(EOFs);
				stringtree_append_tree(root, text);
				free_stringtree(text);
			}
			else if (!strncmp(old, "REDUCTION_RULE_SWITCH", len))
			{
				stringtree_append_tree(root, reductionrules_text);
			}
			else if (!strncmp(old, "TYPES", len))
			{
				stringtree_append_tree(root, shared.tqueue->text);
			}
			else if (!strncmp(old, "SUBTYPES", len))
			{
				stringtree_append_tree(root, shared.stqueue->text);
			}
			else if (!strncmp(old, "FUNCTIONS", len))
			{
				stringtree_append_tree(root, shared.fqueue->text);
			}
			else if (!strncmp(old, "DECLARE_ENVIRONMENT", len))
			{
				stringtree_append_tree(root, declare_environment_text);
			}
			else if (!strncmp(old, "ASSIGN_ENVIRONMENT", len))
			{
				stringtree_append_tree(root, assign_environment_text);
			}
			else if (!strncmp(old, "ASSIGN_SETS", len))
			{
				stringtree_append_tree(root, assign_sets_text);
			}
			else if (!strncmp(old, "STATEMENTS", len))
			{
				stringtree_append_tree(root, statements_text);
			}
			else if (!strncmp(old, "FREE_ENVIRONMENT", len))
			{
				stringtree_append_tree(root, free_environment_text);
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
	
	free_stringtree(declare_environment_text);
	
	free_stringtree(assign_environment_text);
	
	free_stringtree(free_environment_text);
	
	free_stringtree(assign_sets_text);
	
	free_stringtree(statements_text);
	
	free_stringtree(reductionrules_text);
	
	free_type_queue(shared.tqueue);
	
	free_subtype_queue(shared.stqueue);
	
	free_function_queue(shared.fqueue);
	
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
	
	EXIT;
	return root;
}

