
#include <debug.h>

#include "../struct.h"

#include <type/inc.h>
#include <type/grammar/struct.h>
#include <type/grammar/new.h>

#include "grammar.h"

struct type* type_cache_get_grammar_type(
	struct type_cache* this,
	struct structinfo* structinfo)
{
	struct type* retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &(struct grammar_type){
		.super.kind = tk_grammar,
		.structinfo = structinfo
	});
	
	if (node)
	{
		retval = inc_type(node->item);
	}
	else
	{
		struct type* grammar = new_grammar_type(structinfo);
		
		avl_insert(this->tree, grammar);
		
		retval = inc_type(grammar);
	}
	
	EXIT;
	return retval;
}















