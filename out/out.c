
#include <assert.h>

#include <string.h>

#include <debug.h>

#include <quack/new.h>
#include <quack/foreach.h>
/*#include <quack/free.h>*/

/*#include <set/string/new.h>*/
/*#include <set/string/free.h>*/

#include <set/ptr/new.h>
#include <set/ptr/add.h>

#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <string/new.h>
#include <string/free.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_strndup.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <set/ptr/free.h>

#include <lex/state/struct.h>

#include <yacc/state/struct.h>

#include <assertion/print_source.h>

#include <type_cache/get_type/grammar.h>

#include <list/assertion/foreach.h>

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

#include "dynvector/new.h"
#include "dynvector/print_source.h"
#include "dynvector/set.h"
#include "dynvector/free.h"

#include "dyntable/new.h"
#include "dyntable/print_source.h"
#include "dyntable/set.h"
#include "dyntable/free.h"

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
#include "function_queue/submit_free.h"
#include "function_queue/process.h"
#include "function_queue/free.h"

#include "subtype_queue/struct.h"
#include "subtype_queue/new.h"
#include "subtype_queue/process.h"
#include "subtype_queue/free.h"

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
	struct stringset* grammar_sets,
	struct declaration_list* declarations,
	struct assertion_list* assertions,
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
	
	// look through declarations, build environment struct
	// and destructors
	// all in the declaration-queue, right?
	
	TODO;
	#if 0
	struct out_shared shared;
	
	shared.tcache = tcache;
	
	shared.tqueue = new_type_queue();
	
	shared.stqueue = new_subtype_queue();
	
	shared.fqueue = new_function_queue();
	
	struct set_queue* squeue = new_set_queue();
	
	struct declare_queue* dqueue = new_declare_queue();
	
	struct stringtree* assertions_text = new_stringtree();
	
	assertion_list_foreach(assertions, ({
		void runme(struct assertion* assertion)
		{
			struct stringtree* text = assertion_print_source(assertion, &shared);
			
			stringtree_append_tree(assertions_text, text);
			
			free_stringtree(text);
		}
		runme;
	}));
	
	declare_queue_process(dqueue, declarations, &shared);
	
	set_queue_process(squeue, grammar_types, grammar_sets, &shared);
	
	struct stringtree* reductionrules_text = reducerule_to_id_print_source(rrtoi, stoi, grammar_sets, &shared);
	
	struct stringtree* free_start_text = new_stringtree();
	
	struct string* start_string = new_string("$start", 6);
	
	{
		struct type* type = type_cache_get_grammar_type(tcache, start_string);
		unsigned free_id = function_queue_submit_free(shared.fqueue, type);
		stringtree_append_printf(free_start_text, "func_%u", free_id);
	}
	
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
			else if (!strncmp(old, "START_GRAMMAR_ID", len))
			{
				stringtree_append_printf(root, "%u", string_to_id(stoi, start_string));
			}
			else if (!strncmp(old, "FREE_START", len))
			{
				stringtree_append_tree(root, free_start_text);
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
			else if (!strncmp(old, "INIT_DECLARES", len))
			{
				stringtree_append_tree(root, dqueue->init_text);
			}
			else if (!strncmp(old, "ASSIGN_DECLARES", len))
			{
				stringtree_append_tree(root, dqueue->assign_text);
			}
			else if (!strncmp(old, "UNINIT_DECLARES", len))
			{
				stringtree_append_tree(root, dqueue->uninit_text);
			}
			else if (!strncmp(old, "INIT_SETS", len))
			{
				stringtree_append_tree(root, squeue->init_text);
			}
			else if (!strncmp(old, "ASSIGN_SETS", len))
			{
				stringtree_append_tree(root, squeue->assign_text);
			}
			else if (!strncmp(old, "UNINIT_SETS", len))
			{
				stringtree_append_tree(root, squeue->uninit_text);
				
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
	
	free_string(start_string);
	
	free_stringtree(reductionrules_text);
	
	free_stringtree(free_start_text);
	
	free_type_queue(shared.tqueue);
	
	free_subtype_queue(shared.stqueue);
	
	free_function_queue(shared.fqueue);
	
	free_set_queue(squeue);
	
	free_declare_queue(dqueue);
	
	free_stringtree(assertions_text);
	
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
	#endif
}

