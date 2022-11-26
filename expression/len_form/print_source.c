
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_free.h>

#include <type/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* len_form_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	struct len_form_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, "({");
	
	stringtree_append_printf(tree, "struct type_%u* object = ", this->object->type->id);
	
	struct stringtree* subtree = expression_print_source(this->object, shared, environment);
	
	stringtree_append_tree(tree, subtree);
	
	stringtree_append_printf(tree, ";");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "struct type_%u* len = func_%u();", super->type->id, new_id);
	
	switch (this->object->type->kind)
	{
		case tk_string:
			stringtree_append_printf(tree, "mpz_set_ui(len->value, object->len);");
			break;
		
		case tk_list:
			stringtree_append_printf(tree, "mpz_set_ui(len->value, object->n);");
			break;
		
		case tk_dict:
			stringtree_append_printf(tree, "mpz_set_ui(len->value, object->n);");
			break;
		
		case tk_set:
			stringtree_append_printf(tree, "mpz_set_ui(len->value, object->n);");
			break;
		
		default:
			TODO;
			break;
	}
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, this->object->type);
	
	stringtree_append_printf(tree, "func_%u(object);", free_id);
	
	stringtree_append_printf(tree, "len;");
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
}














