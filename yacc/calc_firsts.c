
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>
#include <string/compare.h>
#include <string/free.h>

#include <avl/alloc_tree.h>
#include <avl/search.h>
#include <avl/foreach.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

/*#include <named/unsignedset/struct.h>*/
/*#include <named/unsignedset/new.h>*/
/*#include <named/unsignedset/compare.h>*/
/*#include <named/unsignedset/free.h>*/

#include <named/stringset/struct.h>
#include <named/stringset/new.h>
#include <named/stringset/compare.h>
#include <named/stringset/free.h>

#include <named/trie/struct.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/update.h>
#include <set/unsigned/inc.h>
#include <set/unsigned/free.h>

#include <set/string/new.h>
#include <set/string/add.h>
#include <set/string/foreach.h>

#include "trie/struct.h"

#include "calc_firsts.h"

static struct firsts_node* new_firsts_node(
	struct string* name,
	struct unsignedset* tokens)
{
	ENTER;
	
	struct firsts_node* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	this->tokens = inc_unsignedset(tokens);
	
	EXIT;
	return this;
	
}

static int compare_firsts_nodes(const void* a, const void* b)
{
	const struct firsts_node* const A = a, *const B = b;
	return compare_strings(A->name, B->name);
}

static void free_firsts_node(void* a)
{
	struct firsts_node* node = a;
	free_string(node->name);
	free_unsignedset(node->tokens);
	free(node);
}

static struct stringset* get(struct avl_tree_t* tree, struct string* name)
{
	struct avl_node_t* node = avl_search(tree, &name);
	
	if (node)
	{
		struct named_stringset* nss = node->item;
		
		return nss->stringset;
	}
	else
	{
		struct stringset* ss = new_stringset();
		
		avl_insert(tree, new_named_stringset(name, ss));
		
		return ss;
	}
}

static void add(struct avl_tree_t* tree, struct string* name, struct string* addme)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(tree, &name);
	
	if (node)
	{
		struct named_stringset* nss = node->item;
		
		stringset_add(nss->stringset, addme);
	}
	else
	{
		struct stringset* ss = new_stringset();
		
		stringset_add(ss, addme);
		
		avl_insert(tree, new_named_stringset(name, ss));
	}
	
	EXIT;
}

struct firsts_node* get_firsts(struct avl_tree_t* named_firsts, struct string* name)
{
	struct avl_node_t* node = avl_search(named_firsts, &name);
	assert(node);
	return node->item;
}

struct avl_tree_t* calc_firsts(struct avl_tree_t* named_tries)
{
	ENTER;
	
	struct avl_tree_t* named_firsts = avl_alloc_tree(compare_firsts_nodes, free_firsts_node);
	
	struct avl_tree_t* dependent_on = avl_alloc_tree(compare_named_stringsets, free_named_stringset);
	
	struct avl_tree_t* dependent_of = avl_alloc_tree(compare_named_stringsets, free_named_stringset);
	
	struct quack* todo = new_quack();
	
	avl_foreach(named_tries, ({
		void runme(void* ptr)
		{
			struct named_trie* ntrie = ptr;
			
			struct string* name = ntrie->name;
			
			struct trie* trie = ntrie->trie;
			
			struct unsignedset* tokens = new_unsignedset();
			
			for (unsigned i = 0, n = trie->transitions.n; i < n; i++)
			{
				unsignedset_add(tokens, trie->transitions.data[i]->token);
			}
			
			for (unsigned i = 0, n = trie->grammars.n; i < n; i++)
			{
				struct string* const grammar = trie->grammars.data[i]->grammar;
				
				add(dependent_on, name, grammar);
				add(dependent_of, grammar, name);
			}
			
			avl_insert(named_firsts, new_firsts_node(name, tokens));
			
			quack_append(todo, name);
			
			free_unsignedset(tokens);
		}
		runme;
	}));
	
/*	dotout(named_firsts, dependent_of, NULL);*/
	
	// percolate:
	while (quack_is_nonempty(todo))
	{
		struct string* name = quack_pop(todo);
		
		struct firsts_node* node = get_firsts(named_firsts, name);
		
		bool has_changed = false;
		
		stringset_foreach(get(dependent_on, name), ({
			void runme(struct string* dep_name)
			{
				struct firsts_node* dep_on = get_firsts(named_firsts, dep_name);
			
				if (unsignedset_update(node->tokens, dep_on->tokens))
					has_changed = true;
			}
			runme;
		}));
		
		if (has_changed)
		{
			stringset_foreach(get(dependent_of, name), ({
				void runme(struct string* dep_name) {
					quack_append(todo, dep_name);
				}
				runme;
			}));
		}
		
/*		dotout(named_firsts, dependent_of, name);*/
	}
	
	free_quack(todo);
	
	avl_free_tree(dependent_on);
	
	avl_free_tree(dependent_of);
	
	EXIT;
	return named_firsts;
}










