
#include <unistd.h>
#include <stdio.h>
#include <inttypes.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>
#include <avl/foreach.h>
#include <avl/search.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <quack/new.h>
#include <quack/pop.h>
#include <quack/is_nonempty.h>
#include <quack/append.h>
#include <quack/free.h>

#include <heap/new.h>
#include <heap/is_nonempty.h>
#include <heap/pop.h>
#include <heap/push.h>
#include <heap/free.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/clone.h>
#include <set/ptr/contains.h>
#include <set/ptr/foreach.h>
#include <set/ptr/get_head.h>
#include <set/ptr/discard.h>
#include <set/ptr/free.h>

#include <set/unsigned/compare.h>
#include <set/unsigned/inc.h>

#include <yacc/state/struct.h>

#include <statement/struct.h>
#include <statement/parse/struct.h>
#include <list/statement/foreach.h>

#ifdef VERBOSE
#include <heap/len.h>

#include <quack/len.h>

#include <set/ptr/len.h>

#include <misc/default_sighandler.h>
#endif

#include "struct.h"
#include "minimize_lexer.h"

#include "state/struct.h"
#include "state/new.h"
#include "state/free.h"

#include "build_tokenizer/node/struct.h"

struct pair
{
	struct lex_state *a, *b;
};

static struct pair* new_pair(struct lex_state* a, struct lex_state* b)
{
	ENTER;
	
	struct pair* this = smalloc(sizeof(*this));
	
	assert(a < b);
	
	this->a = a;
	this->b = b;
	
	EXIT;
	return this;
}

static int compare_pairs(const void* a, const void* b)
{
	int cmp = 0;
	const struct pair *A = a, *B = b;
	ENTER;
	
	if (A->a > B->a)
		cmp = +1;
	else if (A->a < B->a)
		cmp = -1;
	else if (A->b > B->b)
		cmp = +1;
	else if (A->b < B->b)
		cmp = -1;
	
	EXIT;
	return cmp;
}

struct dependent_of_node
{
	struct pair pair;
	
	struct avl_tree_t* dependent_of;
};


static struct dependent_of_node* new_dependent_of_node(
	struct lex_state* a, struct lex_state* b)
{
	ENTER;
	
	struct dependent_of_node* this = smalloc(sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->dependent_of = avl_alloc_tree(compare_pairs, free);
	
	EXIT;
	return this;
}

static int compare_dependent_of_nodes(const void* a, const void* b)
{
	int cmp = 0;
	const struct dependent_of_node *A = a, *B = b;
	ENTER;
	
	cmp = compare_pairs(&A->pair, &B->pair);
	
	EXIT;
	return cmp;
}


static void free_dependent_of_node(void* ptr)
{
	struct dependent_of_node* this = ptr;
	ENTER;
	
	avl_free_tree(this->dependent_of);
	
	free(this);
	
	EXIT;
}

struct same_as_node
{
	struct lex_state* state;
	
	struct ptrset* set;
};

static struct same_as_node* new_same_as_node(
	struct lex_state* state, struct ptrset* set)
{
	ENTER;
	
	struct same_as_node* this = smalloc(sizeof(*this));
	
	this->state = state;
	
	this->set = set;
	
	EXIT;
	return this;
}

static int compare_same_as_nodes(const void* a, const void* b)
{
	int cmp = 0;
	const struct same_as_node* A = a, *B = b;
	ENTER;
	
	if (A->state > B->state)
		cmp = +1;
	else if (A->state < B->state)
		cmp = -1;
	else
		cmp = +0;
	
	EXIT;
	return cmp;
}

static void free_same_as_node(void* ptr)
{
	struct same_as_node* this = ptr;
	ENTER;
	
	free_ptrset(this->set);
	
	free(this);
	
	EXIT;
}

struct task
{
	struct pair pair;
	
	unsigned hopcount;
};


static struct task* new_task(
	struct lex_state* a, struct lex_state* b,
	unsigned hopcount)
{
	ENTER;
	
	struct task* this = smalloc(sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->hopcount = hopcount;
	
	EXIT;
	return this;
}

static int compare_tasks(const void* a, const void* b)
{
	const struct task* A = a, *B = b;
	int cmp;
	ENTER;
	
	dpv(A->hopcount);
	dpv(B->hopcount);
	
	if (A->hopcount > B->hopcount)
		cmp = +1;
	else if (A->hopcount < B->hopcount)
		cmp = -1;
	else
		cmp = +0;
	
	EXIT;
	return cmp;
}


static void add_dep(
	struct avl_tree_t* dependent_of,
	struct lex_state* a_on, struct lex_state* b_on,
	struct lex_state* a_of, struct lex_state* b_of)
{
	ENTER;
	
	if (a_of > b_of)
	{
		struct lex_state* swap = b_of;
		b_of = a_of, a_of = swap;
	}
	
	struct avl_node_t* node = avl_search(dependent_of, &(struct pair){a_of, b_of});
	
	if (node)
	{
		struct dependent_of_node* old = node->item;
		
		if (!avl_search(old->dependent_of, &(struct pair){a_on, b_on}))
		{
			struct pair* dep = new_pair(a_on, b_on);
			
			avl_insert(old->dependent_of, dep);
		}
	}
	else
	{
		struct dependent_of_node* new = new_dependent_of_node(a_of, b_of);
		
		struct pair* dep = new_pair(a_on, b_on);
		
		avl_insert(new->dependent_of, dep);
		
		avl_insert(dependent_of, new);
	}
	
	EXIT;
}

static struct ptrset* build_universe(struct lex* this)
{
	ENTER;
	
	struct ptrset* universe = new_ptrset();
	
	struct quack* todo = new_quack();
	
	avl_foreach(this->tokenizer_cache, ({
		void runme(void* ptr)
		{
			struct build_tokenizer_node* ele = ptr;
			
			ptrset_add(universe, ele->start);
			
			quack_append(todo, ele->start);
		}
		runme;
	}));
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler2(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + quack_len(todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "guardian: minimizing tokenizer (build universe): %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler2);
	#endif
	
	while (quack_is_nonempty(todo))
	{
		struct lex_state* state = quack_pop(todo);
		
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct lex_state* const to = state->transitions[i];
			
			if (to && ptrset_add(universe, to))
				quack_append(todo, to);
		}
		
		if (state->EOF_transition_to)
		{
			struct lex_state* const to = state->EOF_transition_to;
			
			if (ptrset_add(universe, to))
				quack_append(todo, to);
		}
		
		#ifdef VERBOSE
		completed++;
		#endif
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	free_quack(todo);
	
	EXIT;
	return universe;
}

static bool mark_as_unequal(
	struct avl_tree_t* connections,
	struct pair* pair)
{
	ENTER;
	
	struct avl_node_t* a_node = avl_search(connections, &pair->a);
	struct avl_node_t* b_node = avl_search(connections, &pair->b);
	
	assert(a_node && b_node);
	
	struct same_as_node* a_sa = a_node->item, *b_sa = b_node->item;
	
	bool removed = false;
	
	if (ptrset_contains(a_sa->set, pair->b))
	{
		assert(ptrset_contains(b_sa->set, pair->a));
		
		ptrset_discard(a_sa->set, pair->b);
		ptrset_discard(b_sa->set, pair->a);
		
		removed = true;
	}
	
	dpvb(removed);
	
	EXIT;
	return removed;
}

struct mapping
{
	struct lex_state* old;
	struct lex_state* new;
};

static struct mapping* new_mapping(struct lex_state* old, struct lex_state* new)
{
	struct mapping* this = smalloc(sizeof(*this));
	this->old = old, this->new = new;
	return this;
}

static int compare_mappings(const void* a, const void* b)
{
	const struct mapping* A = a, *B = b;
	
	if (A->old > B->old)
		return +1;
	else if (A->old < B->old)
		return -1;
	else
		return  0;
}

static struct lex_state* find(struct avl_tree_t* connections, struct lex_state* a)
{
	struct avl_node_t* node = avl_search(connections, &a);
	
	assert(node);
	
	struct same_as_node* sa = node->item;
	
	return ptrset_get_head(sa->set);
}

static void traverse_and_clone(
	struct avl_tree_t* connections,
	struct statement_list* statements)
{
	ENTER;
	
	struct quack* yacc_todo = new_quack();
	
	struct quack* lex_todo = new_quack();
	
	struct ptrset* yacc_queued = new_ptrset();
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free);
	
	
	statement_list_foreach(statements, ({
		void runme(struct statement* statement)
		{
			if (statement->kind == sk_parse)
			{
				struct parse_statement* pstatement = (void*) statement;
				
				struct yacc_state* state = pstatement->ystate;
				
				if (ptrset_add(yacc_queued, state))
					quack_append(yacc_todo, state);
			}
		}
		runme;
	}));
	
	while (quack_is_nonempty(yacc_todo))
	{
		struct yacc_state* state = quack_pop(yacc_todo);
		
		struct lex_state* cloneme = find(connections, state->tokenizer_start);
		
		struct avl_node_t* node = avl_search(mappings, &cloneme);
		
		if (node)
		{
			state->tokenizer_start = ((struct mapping*) node->item)->new;
		}
		else
		{
			struct lex_state* substate = new_lex_state();
			
			struct mapping* submapping = new_mapping(cloneme, substate);
			
			state->tokenizer_start = substate;
			
			avl_insert(mappings, submapping);
			
			quack_append(lex_todo, submapping);
		}
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct yacc_state* const to = state->transitions.data[i]->to;
			
			if (ptrset_add(yacc_queued, to))
				quack_append(yacc_todo, to);
		}
		
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct yacc_state* const to = state->grammar_transitions.data[i]->to;
			
			if (ptrset_add(yacc_queued, to))
				quack_append(yacc_todo, to);
		}
	}
	
	while (quack_is_nonempty(lex_todo))
	{
		struct mapping* mapping = quack_pop(lex_todo);
		
		struct lex_state* const old = mapping->old;
		struct lex_state* const new = mapping->new;
		
		new->accepts = inc_unsignedset(old->accepts);
		
		new->kind = old->kind;
		
		// for each transition:
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct lex_state* to = old->transitions[i];
			
			if (to)
			{
				struct lex_state* subold = find(connections, to);
				
				struct avl_node_t* node = avl_search(mappings, &subold);
				
				if (node)
				{
					struct mapping* submapping = node->item;
					
					new->transitions[i] = submapping->new;
				}
				else
				{
					struct lex_state* substate = new_lex_state();
					
					struct mapping* submapping = new_mapping(subold, substate);
					
					new->transitions[i] = substate;
					
					avl_insert(mappings, submapping);
					
					quack_append(lex_todo, submapping);
				}
			}
		}
		
		// EOF transitions?
		if (old->EOF_transition_to)
		{
			struct lex_state* subold = find(connections, old->EOF_transition_to);
			
			struct avl_node_t* node = avl_search(mappings, &subold);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				new->EOF_transition_to = submapping->new;
			}
			else
			{
				struct lex_state* substate = new_lex_state();
				
				struct mapping* submapping = new_mapping(subold, substate);
				
				new->EOF_transition_to = substate;
				
				avl_insert(mappings, submapping);
				
				quack_append(lex_todo, submapping);
			}
		}
	}
	
	free_ptrset(yacc_queued);
	
	avl_free_tree(mappings);
	
	free_quack(yacc_todo);
	
	free_quack(lex_todo);
	
	EXIT;
}

void lex_minimize_lexer(
	struct lex* this,
	struct statement_list* statements)
{
	ENTER;
	
	struct ptrset* universe = build_universe(this);
	
	struct avl_tree_t* dependent_of = avl_alloc_tree(compare_dependent_of_nodes, free_dependent_of_node);
	
	struct heap* todo = new_heap(compare_tasks);
	
	#ifdef VERBOSE
	uintmax_t count = 0, n = ptrset_len(universe);
	
	dpv(n);
	
	n = (n * (n - 1)) / 2;
	
	dpv(n);
	
	void handler1(int _)
	{
		char ptr[1000] = {};
		
		size_t len = snprintf(ptr, 1000,
			"\e[K" "guardian: minimizing tokenizer (build dependencies): %ju of %ju (%.2f%%)\r",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler1);
	#endif
	
	ptrset_foreach(universe, ({
		void runme(void* a_ptr) {
			ptrset_foreach(universe, ({
				void runme(void* b_ptr) {
					if (a_ptr < b_ptr)
					{
						ENTER;
						
						struct lex_state* a = a_ptr;
						struct lex_state* b = b_ptr;
						
						bool unequal = false;
						
						if (!a->accepts != !b->accepts)
							unequal = true;
						else if (a->accepts && b->accepts && (a->kind != b->kind || compare_unsignedsets(a->accepts, b->accepts)))
							unequal = true;
						else if (!a->EOF_transition_to != !b->EOF_transition_to)
							unequal = true;
						else if (a->EOF_transition_to && b->EOF_transition_to)
							add_dep(dependent_of, a, b, a->EOF_transition_to, b->EOF_transition_to);
							
						for (unsigned i = 0, n = 256; !unequal && i < n; i++)
						{
							struct lex_state* at = a->transitions[i];
							struct lex_state* bt = b->transitions[i];
							
							if (!at != !bt)
								unequal = true;
							else if (at && bt)
								add_dep(dependent_of, a, b, at, bt);
						}
						
						if (unequal)
							heap_push(todo, new_task(a, b, 0));
						
						#ifdef VERBOSE
						count++;
						#endif
						
						EXIT;
					}
				}
				runme;
			}));
		}
		runme;
	}));
	
	#ifdef VERBOSE
	void handler12(int _)
	{
		char ptr[1000] = {};
		
		size_t len = snprintf(ptr, 1000,
			"\e[K" "guardian: minimizing tokenizer (allocating dependency-trees): %ju of %ju (%.2f%%)\r",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	count = 0, n = ptrset_len(universe);
	
	signal(SIGALRM, handler12);
	#endif
	
	struct avl_tree_t* connections = avl_alloc_tree(compare_same_as_nodes, free_same_as_node);
	
	ptrset_foreach(universe, ({
		void runme(void* ptr) {
			ENTER;
			
			struct lex_state* a = ptr;
			
			struct ptrset* uni = ptrset_clone(universe);
			
			struct same_as_node* sa = new_same_as_node(a, uni);
			
			avl_insert(connections, sa);
			
			#ifdef VERBOSE
			count++;
			#endif
			
			EXIT;
		}
		runme;
	}));
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler2(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + heap_len(todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "guardian: minimizing tokenizer (percolate): %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler2);
	#endif
	
	while (heap_is_nonempty(todo))
	{
		struct task* task = heap_pop(todo);
		
		if (mark_as_unequal(connections, &task->pair))
		{
			struct avl_node_t* node = avl_search(dependent_of, &task->pair);
			
			if (node)
			{
				struct dependent_of_node* dep = node->item;
				
				unsigned hopcount = task->hopcount + 1;
				
				avl_foreach(dep->dependent_of, ({
					void runme(void* ptr) {
						const struct pair* pair = ptr;
						
						heap_push(todo, new_task(pair->a, pair->b, hopcount));
					}
					runme;
				}));
			}
		}
		
	    #ifdef VERBOSE
        completed++;
        #endif
		
		free(task);
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	traverse_and_clone(connections, statements);
	
	struct ptrset* freed = new_ptrset();
	
	ptrset_foreach(universe, ({
		void runme(void* ptr) {
			struct lex_state* state = ptr;
			free_lex_state(freed, state);
		}
		runme;
	}));
	
	free_ptrset(freed);
	
	avl_free_tree(dependent_of);
	
	free_ptrset(universe);
	
	avl_free_tree(connections);
	
	free_heap(todo);
	
	EXIT;
}














