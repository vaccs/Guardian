
#include <assert.h>

#include <debug.h>

/*#include <avl/tree.h>*/

/*#include "node/struct.h"*/

/*#include "struct.h"*/
#include "foreach.h"

void stateinfo_foreach(
	struct stateinfo* this,
	void (*runme)(struct trie* trie, struct unsignedset* tokens))
{
	ENTER;
	
	TODO;
	#if 0
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct stateinfo_node* ele = node->item;
		runme(ele->trie, ele->tokens);
	}
	#endif
	
	EXIT;
}


void stateinfo_foreach2(
	struct stateinfo* this,
	void (*runme)(struct stateinfo_node* ele))
{
	ENTER;
	
	TODO;
	#if 0
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		runme(node->item);
	}
	#endif
	
	EXIT;
}

