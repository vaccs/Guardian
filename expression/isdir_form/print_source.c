
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

struct stringtree* isdir_form_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	struct isdir_form_expression* this = (void*) super;
	
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
		stringtree_append_printf(tree, "unsigned char* buffer = malloc(path->len + 1);");
		
		stringtree_append_printf(tree, "memcpy(buffer, path->chars, path->len);");
		
		stringtree_append_printf(tree, "buffer[path->len] = 0;");
		
		stringtree_append_printf(tree, "struct stat statbuf;");
		
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree, ""
			"struct type_%u* result = func_%u("
				"stat((char*) buffer, &statbuf) < 0 || S_ISDIR(statbuf.st_mode));",
			super->type->id, new_id);
			
		stringtree_append_printf(tree, "free(buffer);");
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














