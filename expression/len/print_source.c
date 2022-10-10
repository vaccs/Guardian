
#include <debug.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_free.h>

#include <type/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* len_expression_print_source(
	struct expression* super,
	struct out_shared* shared)
{
	ENTER;
	
	struct len_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	struct expression* list = this->list;
	
	struct type* rtype = super->type;
	
	struct type* ltype = list->type;
	
	type_queue_submit(shared->tqueue, rtype);
	type_queue_submit(shared->tqueue, ltype);
	
	unsigned rtype_id = rtype->id;
	unsigned ltype_id = ltype->id;
	
	stringtree_append_printf(tree, ""
		"({"
			"type_%u* list = "
	"", ltype_id);
	
	struct stringtree* expression = expression_print_source(this->list, shared);
	
	stringtree_append_tree(tree, expression);
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, rtype);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, ltype);
	
	stringtree_append_printf(tree, ""
			";"
			"type_%u* len = func_%u();"
			"mpz_set_ui(len->value, list->n);"
			"func_%u(list);"
			"len;"
		"})"
	"", rtype_id, new_id, free_id);
	
	free_stringtree(expression);
	
	EXIT;
	return tree;
}














