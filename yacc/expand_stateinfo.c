
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/search.h>
#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <named/trie/struct.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/update.h>
#include <set/unsigned/free.h>

#include "trie/struct.h"

#include "stateinfo/node/struct.h"
#include "stateinfo/get_lookaheads.h"
#include "stateinfo/foreach.h"
#include "stateinfo/add.h"

#include "calc_firsts.h"
#include "expand_stateinfo.h"

struct trieset
{
	struct avl_tree_t* tree;
};

static int trieset_node_compare(const void* a, const void* b)
{
	if (a > b)
		return +1;
	else if (a < b)
		return -1;
	else
		return +0;
}

static struct trieset* new_trieset()
{
	ENTER;
	
	struct trieset* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(trieset_node_compare, NULL);
	
	EXIT;
	return this;
}

static void trieset_add(struct trieset* this, struct trie* trie)
{
	ENTER;
	
	avl_insert(this->tree, trie);
	
	EXIT;
}

static void trieset_foreach(
	const struct trieset* this,
	void (*runme)(struct trie* subtrie))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
		runme(node->item);
	
	EXIT;
}

static void free_trieset(struct trieset* this)
{
	avl_free_tree(this->tree);
	free(this);
}

struct trie_to_trieset
{
	struct trie* trie;
	struct trieset* trieset;
};

static struct trie_to_trieset* new_trie_to_trieset(struct trie* trie, struct trieset* trieset)
{
	ENTER;
	
	struct trie_to_trieset* this = smalloc(sizeof(*this));
	
	this->trie = trie;
	this->trieset = trieset;
	
	EXIT;
	return this;
}

static int compare_trie_to_triesets(const void* a, const void* b)
{
	const struct trie_to_trieset *A = a, *B = b;
	if (A->trie > B->trie)
		return +1;
	if (A->trie < B->trie)
		return -1;
	return 0;
}

static void free_trie_to_trieset(void* ptr)
{
	struct trie_to_trieset* this = ptr;
	free_trieset(this->trieset);
	free(this);
}

static void add_dep(struct avl_tree_t* tree, struct trie* trie1, struct trie* trie2)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(tree, &trie1);
	
	if (node)
	{
		struct trie_to_trieset* old = node->item;
		
		trieset_add(old->trieset, trie2);
	}
	else
	{
		struct trieset* trieset = new_trieset();
		
		trieset_add(trieset, trie2);
		
		struct trie_to_trieset* new = new_trie_to_trieset(trie1, trieset);
		
		avl_insert(tree, new);
	}
	
	EXIT;
}

static struct trieset* get_deps(struct avl_tree_t* tree, struct trie* trie)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(tree, &trie);
	
	if (node)
	{
		struct trie_to_trieset* old = node->item;
		EXIT;
		return old->trieset;
	}
	else
	{
		struct trieset* empty = new_trieset();
		
		avl_insert(tree, new_trie_to_trieset(trie, empty));
		
		EXIT;
		return empty;
	}
}

void expand_stateinfo(
	struct stateinfo* stateinfo,
	struct avl_tree_t* named_tries,
	struct avl_tree_t* named_firsts)
{
	ENTER;
	
	struct quack* explore = new_quack();
	
	struct quack* percolate = new_quack();
	
	stateinfo_foreach2(stateinfo, ({
		void runme(struct stateinfo_node* ele) {
		
			quack_append(explore, ele);
			
			quack_append(percolate, ele->trie);
		}
		runme;
	}));
	
	struct avl_tree_t* dependent_on = avl_alloc_tree(compare_trie_to_triesets, free_trie_to_trieset);
	
	struct avl_tree_t* dependent_of = avl_alloc_tree(compare_trie_to_triesets, free_trie_to_trieset);
	
	// expand stateinfo, setting up lookahead dependencies:
	while (quack_is_nonempty(explore))
	{
		struct stateinfo_node* node = quack_pop(explore);
		
		struct trie* const trie = node->trie;
		
		for (unsigned i = 0, n = trie->grammars.n; i < n; i++)
		{
			struct trie_grammar_transition *const ele = trie->grammars.data[i];
			
			struct trie* subgrammar_start;
			
			{
				struct avl_node_t* node = avl_search(named_tries, &ele->grammar);
				
				assert(node);
				
				struct named_trie* ntrie = node->item;
				
				subgrammar_start = ntrie->trie;
			}
			
			struct trie* const to = ele->to;
			
			struct unsignedset* tokens = new_unsignedset();
			
			for (unsigned i = 0, n = to->transitions.n; i < n; i++)
			{
				unsignedset_add(tokens, to->transitions.data[i]->token);
			}
			
			for (unsigned i = 0, n = to->grammars.n; i < n; i++)
			{
				struct firsts_node* node = get_firsts(named_firsts, to->grammars.data[i]->grammar);
				
				unsignedset_update(tokens, node->tokens);
			}
			
			if (to->reduce_as)
			{
				add_dep(dependent_on, subgrammar_start, trie);
				add_dep(dependent_of, trie, subgrammar_start);
			}
			
			struct stateinfo_node* node = stateinfo_add(stateinfo, subgrammar_start, tokens);
			
			if (node)
			{
				quack_append(explore, node);
				
				quack_append(percolate, subgrammar_start);
			}
			
			free_unsignedset(tokens);
		}
	}
	
	// percolate lookaheads:
	while (quack_is_nonempty(percolate))
	{
		struct trie* const trie = quack_pop(percolate);
		
		struct stateinfo_node* node = stateinfo_get_lookaheads(stateinfo, trie);
		
		bool has_changed = false;
		
		trieset_foreach(get_deps(dependent_on, trie), ({
			void runme(struct trie* dep)
			{
				struct stateinfo_node* dep_on = stateinfo_get_lookaheads(stateinfo, dep);
				
				if (unsignedset_update(node->tokens, dep_on->tokens))
					has_changed = true;
			}
			runme;
		}));
		
		if (has_changed)
		{
			trieset_foreach(get_deps(dependent_of, trie), ({
				void runme(struct trie* dep) {
					quack_append(percolate, dep);
				}
				runme;
			}));
		}
		
	}
	
	avl_free_tree(dependent_of);
	avl_free_tree(dependent_on);
	
	free_quack(percolate);
	free_quack(explore);
	
	EXIT;
}










