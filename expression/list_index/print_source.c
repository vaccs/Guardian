
#include <debug.h>

/*#include <type/list/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>

#include <type/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* list_index_expression_print_source(
	struct expression* super,
	struct shared* shared)
{
	ENTER;
	
	TODO;
	#if 0
	struct stringtree* tree = new_stringtree();
	
	struct list_index_expression* this = (void*) super;
	
	unsigned rettype_id = out_get_type_id(shared, super->type);
	
	unsigned list_id = out_get_type_id(shared, this->list->type);
	
	assert(this->index->type->kind == tk_int);
	
	unsigned index_id = out_get_type_id(shared, this->index->type);
	
	stringtree_append_printf(tree, "({");
	
	stringtree_append_printf(tree, "type_%u* list = ", list_id);
	stringtree_append_tree(tree, expression_print_source(this->list, shared));
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "type_%u* index = ", index_id);
	stringtree_append_tree(tree, expression_print_source(this->index, shared));
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "type_%u* element = type_%u_index(list, index);", rettype_id, list_id);
	
	stringtree_append_printf(tree, "free_type_%u(list), free_type_%u(index);", list_id, index_id);
	
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












