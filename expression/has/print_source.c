
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_append.h>
#include <out/function_queue/submit_free.h>

#include <type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* has_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	struct has_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, "({");
	
	stringtree_append_printf(tree, "struct type_%u* object = ", this->object->type->id);
	
	struct stringtree* object = expression_print_source(this->object, shared, environment);
	stringtree_append_tree(tree, object);
	stringtree_append_printf(tree, ";");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "struct type_%u* result = func_%u(!!object->$%.*s);",
		super->type->id, new_id, this->fieldname->len, this->fieldname->chars);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, this->object->type);
	stringtree_append_printf(tree, "func_%u(object);", free_id);
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(object);
	
	EXIT;
	return tree;
}














