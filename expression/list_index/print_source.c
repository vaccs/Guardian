
#include <debug.h>

/*#include <type/list/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>

#include <type/struct.h>

#include <out/shared.h>

/*#include <out/type_lookup/lookup.h>*/

/*#include <out/function_lookup/lookup_index.h>*/
/*#include <out/function_lookup/lookup_free.h>*/

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* list_index_expression_print_source(
	struct expression* super,
	struct out_shared* shared)
{
	ENTER;
	
	TODO;
	#if 0
	struct stringtree* tree = new_stringtree();
	
	struct list_index_expression* this = (void*) super;
	
	type_lookup(shared->tlookup, super->type, NULL);
	
	stringtree_append_printf(tree, "({");
	
	unsigned listid = this->list->type->id;
	unsigned indexid = this->index->type->id;
	
	stringtree_append_printf(tree, "type_%u* list = ", listid);
	stringtree_append_tree(tree, expression_print_source(this->list, shared));
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "type_%u* index = ", indexid);
	stringtree_append_tree(tree, expression_print_source(this->index, shared));
	stringtree_append_printf(tree, ";");
	
	unsigned index_func = function_lookup_index(shared->flookup, this->list->type);
	
	stringtree_append_printf(tree, ""
		"type_%u* element = func_%u(list, index);"
	"", super->type->id, index_func);
	
	TODO;
	#if 0
	unsigned free_list_func = function_lookup_free(shared->flookup, this->list->type);
	unsigned free_index_func = function_lookup_free(shared->flookup, this->index->type);
	
	stringtree_append_printf(tree, ""
		"func_%u(list), func_%u(index);"
	"", free_list_func, free_index_func);
	#endif
	
	stringtree_append_printf(tree, "element;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
	#endif
}


/*	stringtree_append_printf(tree, "unsigned long idx;");*/
/*	*/
/*	stringtree_append_printf(tree, "if (mpz_fits_ulong_p(index) || (idx = mpz_get_ui(index)) >= list->n) {");*/
/*	*/
/*	stringtree_append_printf(tree, "assert(!\"TODO\");");*/
/*	*/
/*	stringtree_append_printf(tree, "}");*/
/*	*/
/*	stringtree_append_printf(tree, "type_%u* element = inc_type_%u(list->data[idx]);", rettype_id, rettype_id);*/
/*	*/












