
#include <debug.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_free.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <type/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* isabspath_form_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	struct isabspath_form_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, "({");
	
	{
		stringtree_append_printf(tree, "struct type_%u* path = ", this->path->type->id);
		struct stringtree* subtree = expression_print_source(this->path, shared, environment);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		free_stringtree(subtree);
	}
	
	{
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree, ""
			"struct type_%u* result = func_%u("
				"path->len > 0 && path->chars[0] == '/');",
			super->type->id, new_id);
	}
	
	{
		unsigned free_id = function_queue_submit_free(shared->fqueue, this->path->type);
		stringtree_append_printf(tree, "func_%u(path);", free_id);
	}
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}














