
#include <debug.h>

/*#include <type/list/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <type/struct.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_index.h>
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* list_index_expression_print_source(
	struct expression* super,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct list_index_expression* this = (void*) super;
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, "({");
	
	struct type* list_type = this->list->type;
	type_queue_submit(shared->tqueue, list_type);
	
	struct stringtree* list_tree = expression_print_source(this->list, shared);
	stringtree_append_printf(tree, "struct type_%u* list = ", list_type->id);
	stringtree_append_tree(tree, list_tree);
	stringtree_append_printf(tree, ";");
	free_stringtree(list_tree);
	
	struct type* index_type = this->index->type;
	type_queue_submit(shared->tqueue, index_type);
	
	struct stringtree* index_tree = expression_print_source(this->index, shared);
	stringtree_append_printf(tree, "struct type_%u* index = ", index_type->id);
	stringtree_append_tree(tree, index_tree);
	stringtree_append_printf(tree, ";");
	free_stringtree(index_tree);
	
	unsigned index_id = function_queue_submit_index(shared->fqueue, list_type);
	
	stringtree_append_printf(tree, ""
		"struct type_%u* element = func_%u(list, index);"
	"", super->type->id, index_id);
	
	unsigned free_list_id = function_queue_submit_free(shared->fqueue, list_type);
	
	unsigned free_index_id = function_queue_submit_free(shared->fqueue, index_type);
	
	stringtree_append_printf(tree, ""
		"func_%u(list), func_%u(index);"
	"", free_list_id, free_index_id);
	
	stringtree_append_printf(tree, "element;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
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












