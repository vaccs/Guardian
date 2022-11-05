
#include <debug.h>

#include <avl/insert.h>
#include <avl/search.h>

#include <type/grammar/struct.h>
#include <type/grammar/new.h>

#include "../struct.h"

#include "grammar.h"

struct type* type_cache_get_grammar_type(
	struct type_cache* this,
	struct string* name)
{
	struct type* retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &(struct grammar_type){
		.super.kind = tk_grammar,
		.name = name
	});
	
	if (node)
	{
		retval = node->item;
	}
	else
	{
		struct type* grammar = new_grammar_type(this->next++, name);
		
		avl_insert(this->tree, grammar);
		
		retval = grammar;
	}
	
	EXIT;
	return retval;
}















