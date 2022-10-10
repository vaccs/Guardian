
#include <debug.h>

#include <out/shared.h>
#include <out/type_lookup/lookup.h>
#include <out/function_lookup/lookup_new.h>
#include <out/function_lookup/lookup_free.h>

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
	
	struct type* ltype = list->type;
	
	struct type* rtype = super->type;
	
	type_lookup(shared->tlookup, ltype, NULL);
	type_lookup(shared->tlookup, rtype, NULL);
	
	unsigned ltype_id = ltype->id;
	unsigned rtype_id = rtype->id;
	
	stringtree_append_printf(tree, ""
		"({"
			"type_%u* list = "
	"", ltype_id);
	
	struct stringtree* expression = expression_print_source(this->list, shared);
	
	stringtree_append_tree(tree, expression);
	
	unsigned new_id = function_lookup_new(shared->flookup, rtype);
	
	unsigned free_id = function_lookup_free(shared->flookup, ltype, 0);
	
	stringtree_append_printf(tree, ""
			";"
			"type_%u* len = func_%u();"
			"mpz_set_ul(len->value, list->n);"
			"func_%u(list);"
			"len;"
		"})"
	"", rtype_id, new_id, free_id);
	
	free_stringtree(expression);
	
	EXIT;
	return tree;
}














