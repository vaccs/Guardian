
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <string/new.h>
#include <string/inc.h>
#include <string/free.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/search.h>
#include <avl/free_tree.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

/*#include <named/gegex/struct.h>*/

/*#include <set/unsigned/to_string.h>*/

#include <named/trie/new.h>
/*#include <named/trie/compare.h>*/
/*#include <named/trie/free.h>*/

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

/*#include <set/string/new.h>*/
/*#include <set/string/foreach.h>*/

#include <gegex/grammar/struct.h>
#include <gegex/transition/struct.h>
#include <gegex/struct.h>

#include "reductioninfo/new.h"
#include "reductioninfo/inc.h"
#include "reductioninfo/free.h"

#include "structinfo/inc.h"

#include "trie/struct.h"
#include "trie/new.h"
#include "trie/add_transition.h"
#include "trie/add_grammar_transition.h"

#include "build_tries.h"

struct expand_bundle
{
	struct string* trie_name;
	struct trie* trie;
	struct gegex* gegex;
};

static struct expand_bundle* new_explore_bundle(
	struct string* trie_name, struct trie* trie, struct gegex* gegex)
{
	ENTER;
	
	struct expand_bundle* bundle = smalloc(sizeof(*bundle));
	bundle->trie_name = trie_name;
	bundle->trie = trie;
	bundle->gegex = gegex;
	
	EXIT;
	return bundle;
}

struct gegex_to_trie_name_node
{
	struct gegex* gegex;
	struct string* trie_name;
};

static struct gegex_to_trie_name_node* new_gegex_to_trie_name(
	struct gegex* gegex, struct string* trie_name)
{
	ENTER;
	
	struct gegex_to_trie_name_node* this = smalloc(sizeof(*this));
	this->gegex = gegex;
	this->trie_name = inc_string(trie_name);
	
	EXIT;
	return this;
}

static unsigned trie_id = 0;

void build_tries(
	struct avl_tree_t* named_tries,
	struct string* reduce_as,
	struct gegex* start,
	struct structinfo* structinfo)
{
	ENTER;
	
	assert(reduce_as);
	
	struct quack* explore = new_quack();
	
	struct quack* expand = new_quack();
	
	struct ptrset* seen = new_ptrset();
	
	int compare_gegex_to_trie(const void* a, const void* b)
	{
		const struct gegex_to_trie_name_node *A = a, *B = b;
		if (A->gegex > B->gegex)
			return +1;
		if (A->gegex < B->gegex)
			return -1;
		return +0;
	}
	
	void free_gegex_to_trie(void* a)
	{
		struct gegex_to_trie_name_node* this = a;
		free_string(this->trie_name);
		free(this);
	}
	
	struct avl_tree_t* gegex_to_trie = avl_alloc_tree(compare_gegex_to_trie, free_gegex_to_trie);
	
	// setup:
	{
		ptrset_add(seen, start);
		
		quack_append(explore, start);
		
		avl_insert(gegex_to_trie, new_gegex_to_trie_name(start, reduce_as));
		
		struct trie* trie = new_trie();
		
		struct named_trie* new = new_named_trie(reduce_as, trie);
		
		quack_append(expand, new_explore_bundle(reduce_as, trie, start));
		
		avl_insert(named_tries, new);
	}
	
	// explore:
	while (quack_is_nonempty(explore))
	{
		struct gegex* state = quack_pop(explore);
		
		void process_to(struct gegex* to)
		{
			if (ptrset_add(seen, to))
			{
				quack_append(explore, to);
			}
			else if ((to->transitions.n || to->grammars.n) && !avl_search(gegex_to_trie, &to))
			{
				struct string* name = new_string_from_format("(trie #%u)", trie_id++);
				
				struct trie* trie = new_trie();
				
				struct named_trie* new = new_named_trie(name, trie);
				
				quack_append(expand, new_explore_bundle(name, trie, to));
				
				avl_insert(gegex_to_trie, new_gegex_to_trie_name(to, name));
				
				avl_insert(named_tries, new);
				
				free_string(name);
			}
		}
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			process_to(state->transitions.data[i]->to);
		}
		
		for (unsigned i = 0, n = state->grammars.n; i < n; i++)
		{
			process_to(state->grammars.data[i]->to);
		}
	}
	
	// we have one pass that fills-out all the tries:
	while (quack_is_nonempty(expand))
	{
		struct expand_bundle* bundle = quack_pop(expand);
		
		void expand_helper(
			struct trie* const trie,
			struct gegex* const gegex,
			struct reductioninfo* reductioninfo)
		{
			ENTER;
			
			if (reductioninfo && gegex->accepts)
			{
				trie->reductioninfo = inc_reductioninfo(reductioninfo);
				trie->structinfo = inc_structinfo(structinfo);
				trie->reduce_as = inc_string(bundle->trie_name);
				trie->grammar = inc_string(reduce_as);
			}
			
			struct trie* process_transition(
				struct structinfo* tags, // might be empty
				struct string* grammar, // might be NULL
				struct gegex* to)
			{
				ENTER;
				
				struct reductioninfo* subreductioninfo = new_reductioninfo(grammar ? rik_grammar : rik_token, tags, grammar, reductioninfo);
				
				struct trie* retval = new_trie();
				
				struct avl_node_t* node = avl_search(gegex_to_trie, &to);
				
				if (node)
				{
					if (to->accepts)
					{
						retval->reductioninfo = inc_reductioninfo(subreductioninfo);
						retval->structinfo = inc_structinfo(structinfo);
						retval->reduce_as = inc_string(bundle->trie_name);
						retval->grammar = inc_string(reduce_as);
					}
					
					struct trie* reduce = new_trie();
					
					struct gegex_to_trie_name_node* gtotn = node->item;
					
					trie_add_grammar_transition(retval, gtotn->trie_name, reduce);
					
					reduce->reductioninfo = new_reductioninfo(rik_trie, NULL, gtotn->trie_name, subreductioninfo);
					reduce->structinfo = inc_structinfo(structinfo);
					reduce->reduce_as = inc_string(bundle->trie_name);
					reduce->grammar = inc_string(reduce_as);
				}
				else
				{
					expand_helper(retval, to, subreductioninfo);
				}
				
				free_reductioninfo(subreductioninfo);
				
				EXIT;
				return retval;
			}
			
			for (unsigned i = 0, n = gegex->transitions.n; i < n; i++)
			{
				struct gegex_transition* transition = gegex->transitions.data[i];
				
				struct trie* to = process_transition(transition->structinfo, NULL, transition->to);
				
				trie_add_transition(trie, transition->token, to);
			}
			
			for (unsigned i = 0, n = gegex->grammars.n; i < n; i++)
			{
				struct gegex_grammar_transition* transition = gegex->grammars.data[i];
				
				struct trie* to = process_transition(transition->structinfo, transition->grammar, transition->to);
				
				trie_add_grammar_transition(trie, transition->grammar, to);
			}
			
			EXIT;
		}
		
		expand_helper(bundle->trie, bundle->gegex, NULL);
		
		free(bundle);
	}
	
	avl_free_tree(gegex_to_trie);
	
	free_ptrset(seen);
	
	free_quack(explore);
	
	free_quack(expand);
	
	EXIT;
}




