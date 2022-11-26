
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_append.h>
#include <out/function_queue/submit_free.h>

#include <list/expression/foreach.h>

#include <type/struct.h>
#include <type/lambda/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* filter_form_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	TODO;
	#if 0
	struct filter_form_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "({");
	
	type_queue_submit(shared->tqueue, super->type);
	
	// lambda:
	{
		struct stringtree* subtree = expression_print_source(
			this->lambda, shared, environment);
		
		stringtree_append_printf(tree, ""
			"struct type_%u* lambda = "
		"", this->lambda->type->id);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		
		free_stringtree(subtree);
	}
	
	stringtree_append_printf(tree, "unsigned n = -1;");
	
	unsigned counter = 0;
	
	expression_list_foreach(this->arguments, ({
		void runme(struct expression* expression)
		{
			struct stringtree* subtree = expression_print_source(
				expression, shared, environment);
			
			stringtree_append_printf(tree, ""
				"struct type_%u* list_%u = "
			"", expression->type->id, counter);
			stringtree_append_tree(tree, subtree);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree,
				"if (list_%u->n < n) n = list_%u->n;",
				counter, counter);
			
			free_stringtree(subtree);
			
			counter++;
		}
		runme;
	}));
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree,
		"struct type_%u* result = func_%u();",
		super->type->id, new_id);
	
	stringtree_append_printf(tree, "for (unsigned i = 0; i < n; i++)");
	stringtree_append_printf(tree, "{");
	
	struct type* subresult_type = ((struct lambda_type*) this->lambda->type)->rettype;
	
	stringtree_append_printf(tree, ""
		"struct type_%u* subresult = (lambda->evaluate)(lambda"
	"", subresult_type->id);
	
	counter = 0;
	expression_list_foreach(this->arguments, ({
		void runme(struct expression* expression)
		{
			stringtree_append_printf(tree, ", list_%u->data[i]", counter);
			counter++;
		}
		runme;
	}));
	
	stringtree_append_printf(tree, ");");
	
	{
		unsigned append_id = function_queue_submit_append(shared->fqueue, super->type);
		
		stringtree_append_printf(tree, "func_%u(result, subresult);", append_id);
	}
	
	{
		unsigned free_id = function_queue_submit_free(shared->fqueue, subresult_type);
		
		stringtree_append_printf(tree, "func_%u(subresult);", free_id);
	}
	
	stringtree_append_printf(tree, "}");
	
	counter = 0;
	expression_list_foreach(this->arguments, ({
		void runme(struct expression* expression)
		{
			unsigned free_id = function_queue_submit_free(
				shared->fqueue, expression->type);
			
			stringtree_append_printf(tree, ""
				"func_%u(list_%u);"
			"", free_id, counter++);
		}
		runme;
	}));
	
	{
		unsigned free_id = function_queue_submit_free(shared->fqueue, this->lambda->type);
		
		stringtree_append_printf(tree, "func_%u(lambda);", free_id);
	}
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
	#endif
}














