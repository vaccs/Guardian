
#include <assert.h>

#include <debug.h>

#include <type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/function_queue/submit_new.h>
/*#include <out/function_queue/submit_compare.h>*/
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* string_contains_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	assert(super->kind == ek_string_contains);
	
	struct string_contains_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "({");
	
	struct stringtree* substring = expression_print_source(this->substring, shared, environment);
	stringtree_append_printf(tree, "struct type_%u* substring = ", this->substring->type->id);
	stringtree_append_tree(tree, substring);
	stringtree_append_printf(tree, ";");
	
	struct stringtree* string = expression_print_source(this->string, shared, environment);
	stringtree_append_printf(tree, "struct type_%u* string = ", this->string->type->id);
	stringtree_append_tree(tree, string);
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, 
		"bool found = !!memmem("
			"string->chars, string->len, "
			"substring->chars, substring->len);");
	
	unsigned free_id1 = function_queue_submit_free(shared->fqueue, this->substring->type);
	unsigned free_id2 = function_queue_submit_free(shared->fqueue, this->string->type);
	
	stringtree_append_printf(tree, "func_%u(substring);", free_id1);
	stringtree_append_printf(tree, "func_%u(string);", free_id2);
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "func_%u(found);", new_id);
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(substring);
	free_stringtree(string);
	
	EXIT;
	return tree;
}














