
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
#include <out/function_queue/submit_free.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* assert_statement_print_source(
	struct statement* super,
	struct out_shared* shared,
	struct environment_type* environment_type)
{
	ENTER;
	
	assert(super->kind == sk_assert);
	
	struct assert_statement* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "{");
	
	stringtree_append_printf(tree,
		"struct type_%u* assertion = ",
		this->expression->type->id);
	
	struct stringtree* subtree = expression_print_source(
		this->expression, shared, environment_type);
	
	stringtree_append_tree(tree, subtree);
	
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "if (!assertion->value)");
	
	stringtree_append_printf(tree, "{");
	
	switch (this->kind)
	{
		case ak_error:
		{
			stringtree_append_printf(tree, ""
				"fprintf(stderr, "
					"\"\\e[1m\" \"%%s:\" \"\\e[m \""
					"\"\\e[31m\" \"%%%%error: \""
					"\"assertion failed on line %u!\""
					" \"\\e[m\" \"\\n\", argv0);"
				"exit(1);"
			"", this->line);
			break;
		}
		
		case ak_warning:
		{
			stringtree_append_printf(tree, ""
				"fprintf(stderr, "
					"\"\\e[1m\" \"%%s:\" \"\\e[m \""
					"\"\\e[33m\" \"%%%%warning: \" \"\\e[m\""
					"\"assertion failed on line %u!\""
					"\"\\n\", argv0);"
			"", this->line);
			break;
		}
		
		case ak_note:
		{
			stringtree_append_printf(tree, ""
				"fprintf(stderr, "
					"\"\\e[1m\" \"%%s:\" \"\\e[m \""
					"\"\\e[36m\" \"%%%%note: \" \"\\e[m\""
					"\"assertion failed on line %u!\""
					"\"\\n\", argv0);"
			"", this->line);
			break;
		}
		
		default:
			TODO;
			break;
	}

	stringtree_append_printf(tree, "}");

	unsigned free_id = function_queue_submit_free(shared->fqueue, this->expression->type);

	stringtree_append_printf(tree, "func_%u(assertion);", free_id);

	stringtree_append_printf(tree, "}");

	free_stringtree(subtree);
	
	EXIT;
	return tree;
}











