
#include <debug.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/foreach.h>
#include <set/ptr/compare.h>
#include <set/ptr/free.h>

#include <set/unsigned/new.h>
#include <set/unsigned/update.h>
#include <set/unsigned/free.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/update.h>
#include <yacc/structinfo/free.h>

#include <heap/new.h>
#include <heap/is_nonempty.h>
#include <heap/head.h>
#include <heap/push.h>
#include <heap/pop.h>
#include <heap/free.h>

#include "struct.h"
#include "new.h"
#include "nfa_to_dfa.h"
#include "add_transition.h"

#include "transition/struct.h"

struct mapping
{
	struct ptrset* stateset;
	struct gegex* combined_state;
};

static struct mapping* new_mapping(
	struct ptrset* stateset,
	struct gegex* state)
{
	ENTER;
	
	struct mapping* this = smalloc(sizeof(*this));
	
	this->stateset = stateset;
	this->combined_state = state;
	
	EXIT;
	return this;
}

static int compare_mappings(const void* a, const void* b)
{
	const struct mapping *A = a, *B = b;
	return compare_ptrsets(A->stateset, B->stateset);
}

static void free_mapping(void* a)
{
	struct mapping* this = a;
	ENTER;
	
	free_ptrset(this->stateset);
	free(this);
	
	EXIT;
}

static void add_lambda_states(struct ptrset* set, struct gegex* ele)
{
	ENTER;
	
	if (ptrset_add(set, ele))
	{
		for (unsigned i = 0, n = ele->lambdas.n; i < n; i++)
		{
			add_lambda_states(set, ele->lambdas.data[i]);
		}
	}
	
	EXIT;
}

struct gegex* gegex_nfa_to_dfa(struct gegex* original)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	
	struct gegex* new_start = new_gegex();
	
	{
		struct ptrset* start_set = new_ptrset();
		
		add_lambda_states(start_set, original);
		
		struct mapping* mapping = new_mapping(start_set, new_start);
		
		quack_append(todo, mapping);
		
		avl_insert(mappings, mapping);
	}
	
	while (quack_is_nonempty(todo))
	{
		struct mapping* mapping = quack_pop(todo);
		
		struct ptrset* const stateset = mapping->stateset;
		
		struct gegex* const state = mapping->combined_state;
		
		// set this as reduction_point if any states in list are accepting:
		{
			bool accepts = false;
			
			ptrset_foreach(stateset, ({
				void runme(void* ptr) {
					struct gegex* ele = ptr;
					if (ele->accepts) {
						accepts = true;
					}
				}
				runme;
			}));
			
			state->accepts = accepts;
			
			dpvb(state->accepts);
		}
		
		// iterators for gegex_transitions:
		{
			struct iterator
			{
				struct gegex_transition **i, **n;
			};
			
			struct iterator* new_iterator(struct gegex* state)
			{
				ENTER;
				
				struct iterator* this = smalloc(sizeof(*this));
				
				this->i = state->transitions.data;
				
				this->n = state->transitions.data + state->transitions.n;
				
				EXIT;
				return this;
			}
			
			int compare_iterators(const void* a, const void* b)
			{
				const struct iterator* A = a, *B = b;
				
				unsigned token_a = A->i[0]->token;
				unsigned token_b = B->i[0]->token;
				
				if (token_a > token_b)
					return +1;
				else if (token_a < token_b)
					return -1;
				else
					return 0;
			}
			
			struct heap* heap = new_heap(compare_iterators);
			
			// create iterators for each state:
			ptrset_foreach(stateset, ({
				void runme(void *ptr) {
					struct gegex* ele = ptr;
					if (ele->transitions.n)
					{
						struct iterator* iter = new_iterator(ele);
						heap_push(heap, iter);
					}
				}
				runme;
			}));
			
			while (heap_is_nonempty(heap))
			{
				struct iterator* iterator = heap_head(heap);
				
				struct gegex_transition* transition = iterator->i[0];
				
				unsigned min_token = transition->token;
				
				dpv(min_token);
				
				struct unsignedset* whitespace = new_unsignedset();
				
				struct ptrset* subptrset = new_ptrset();
				
				struct structinfo* structinfo = new_structinfo();
				
				do
				{
					heap_pop(heap);
					
					add_lambda_states(subptrset, transition->to);
					
					unsignedset_update(whitespace, transition->whitespace);
					
					structinfo_update(structinfo, transition->structinfo);
					
					if (++iterator->i < iterator->n)
						heap_push(heap, iterator);
					else
						free(iterator);
				}
				while (heap_is_nonempty(heap) && (transition = (iterator = heap_head(heap))->i[0])->token == min_token);
				
				struct avl_node_t* node = avl_search(mappings, &subptrset);
				
				if (node)
				{
					TODO;
					#if 0
					struct mapping* old = node->item;
					
					gegex_add_transition(state, min_token, whitespace, structinfo, old->combined_state);
					
					free_ptrset(subptrset);
					#endif
				}
				else
				{
					struct gegex* substate = new_gegex();
					
					struct mapping* new = new_mapping(subptrset, substate);
					
					gegex_add_transition(state, min_token, whitespace, structinfo, substate);
					
					quack_append(todo, new);
					
					avl_insert(mappings, new);
				}
				
				free_structinfo(structinfo), free_unsignedset(whitespace);
			}
			
			free_heap(heap);
		}
		
		// iterators for gegex_grammar_transition:
		{
			struct iterator
			{
				struct gegex_grammar_transition **i, **n;
			};
			
			struct iterator* new_iterator(struct gegex* state)
			{
				ENTER;
				
				TODO;
				#if 0
				struct iterator* this = smalloc(sizeof(*this));
				
				this->i = state->grammar_transitions.data;
				
				this->n = state->grammar_transitions.data + state->grammar_transitions.n;
				
				EXIT;
				return this;
				#endif
			}
			
			int compare_iterators(const void* a, const void* b)
			{
				TODO;
				#if 0
				const struct iterator* A = a, *B = b;
				
				struct string* grammar_a = A->i[0]->grammar;
				struct string* grammar_b = B->i[0]->grammar;
				
				return compare_strings(grammar_a, grammar_b);
				#endif
			}
			
			struct heap* heap = new_heap(compare_iterators);
			
			// create iterators for each state:
			ptrset_foreach(stateset, ({
				void runme(void* ptr) {
					struct gegex* ele = ptr;
					if (ele->grammars.n)
					{
						TODO;
						#if 0
						struct iterator* iter = new_iterator(ele);
						heap_push(heap, iter);
						#endif
					}
				}
				runme;
			}));
			
			while (heap_is_nonempty(heap))
			{
				TODO;
				#if 0
				struct iterator* iterator;
				
				struct gegex_grammar_transition* transition;
				
				struct string* min_grammar = (transition = (iterator = heap_head(heap))->i[0])->grammar;
				
				struct ptrset* subptrset = new_ptrset();
				
				struct structinfo* structinfo = new_structinfo(/* name: */ NULL);
				
				while (heap_len(heap) && strings_are_equal((transition = (iterator = heap_head(heap))->i[0])->grammar, min_grammar))
				{
					heap_pop(heap);
					
					add_lambda_states(subptrset, transition->to);
					
					structinfo_update(structinfo, transition->structinfo);
					
					if (++iterator->i < iterator->n)
						heap_push(heap, iterator);
					else
						free(iterator);
				}
				
				struct avl_node_t* node = avl_search(mappings, &subptrset);
				
				if (node)
				{
					struct mapping* old = node->item;
					
					gegex_add_grammar_transition(state, min_grammar, structinfo, old->combined_state);
					
					free_ptrset(subptrset);
				}
				else
				{
					struct gegex* substate = new_gegex();
					
					struct mapping* new = new_mapping(subptrset, substate);
					
					gegex_add_grammar_transition(state, min_grammar, structinfo, substate);
					
					quack_append(todo, new);
					
					avl_insert(mappings, new);
				}
				
				free_structinfo(structinfo);
				#endif
			}
			
			free_heap(heap);
		}
	}
	
	avl_free_tree(mappings);
	
	free_quack(todo);
	
	EXIT;
	return new_start;
}







