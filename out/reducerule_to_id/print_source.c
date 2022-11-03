
#include <debug.h>

#include <avl/tree_t.h>

#include <string/struct.h>

#include <type/struct.h>
#include <type_cache/get_type/grammar.h>

#include <yacc/structinfo/struct.h>
#include <yacc/reductioninfo/print_source.h>

#include "../shared.h"
#include "../type_queue/submit.h"
#include "../string_to_id/string_to_id.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* reducerule_to_id_print_source(
	struct type_cache* tcache,
	struct reducerule_to_id* this,
	struct string_to_id* stoi,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, ""
		"switch (r)"
		"{"
	"");
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct reducerule_to_id_node* const ele = node->item;
		
		stringtree_append_printf(tree, ""
			"case %u:"
			"{"
		"", ele->id);
		
		stringtree_append_printf(tree, ""
			"/* build structs */"
		"");
		
		struct type* type = type_cache_get_grammar_type(tcache, ele->grammar);
		
		type_queue_submit(shared->tqueue, type);
		
		stringtree_append_printf(tree, ""
			"struct type_%u* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));" "\n"
			"value->refcount = 1;" "\n"
		"", type->id);
		
		reductioninfo_print_source(tree, ele->reductioninfo, ele->structinfo, tcache, shared, ele->grammar->chars);
		
		stringtree_append_printf(tree, ""
				"d = value, g = %u;"
				"break;"
			"}"
		"", string_to_id(stoi, ele->reduce_as));
	}
	
	stringtree_append_printf(tree, ""
		"}"
	"");
	
	EXIT;
	return tree;
}

















