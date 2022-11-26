
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <expression/struct.h>
#include <expression/print_source.h>

#include <type/struct.h>

#include <out/shared.h>
#include <out/function_queue/submit_print.h>
#include <out/function_queue/submit_free.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* print_statement_print_source(
	struct statement* super,
	struct out_shared* shared,
	struct type* environment_type)
{
	ENTER;
	
	assert(super->kind == sk_print);
	
	struct print_statement* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "if (verbose)");
	stringtree_append_printf(tree, "{");
	
	stringtree_append_printf(tree, "struct type_%u* printme = ", this->expression->type->id);
	
	struct stringtree* subtree = expression_print_source(this->expression, shared, environment_type);
	
	stringtree_append_tree(tree, subtree);
	
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "printf(\"%%%%print: \");");
	
	unsigned print_id = function_queue_submit_print(shared->fqueue, this->expression->type);
	
	stringtree_append_printf(tree, "func_%u(printme);", print_id);
	
	stringtree_append_printf(tree, "puts(\"\");");
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, this->expression->type);
	
	stringtree_append_printf(tree, "func_%u(printme);", free_id);
	
	stringtree_append_printf(tree, "}");
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
}









