
#include <stdbool.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <type/struct.h>
#include <type/tuple/struct.h>

#include <list/type/foreach.h>

#include <out/shared.h>
/*#include <out/type_lookup/lookup.h>*/
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* tuple_concat_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct tuple_concat_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "({");
	
	type_queue_submit(shared->tqueue, super->type);
	
	struct stringtree* left = expression_print_source(this->left, shared, environment);
	
	struct stringtree* right = expression_print_source(this->right, shared, environment);
	
	stringtree_append_printf(tree, "struct type_%u *left = ", this->left->type->id);
	stringtree_append_tree(tree, left);
	stringtree_append_printf(tree, ";\n");
	
	stringtree_append_printf(tree, "struct type_%u *right = ", this->right->type->id);
	stringtree_append_tree(tree, right);
	stringtree_append_printf(tree, ";\n");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, ""
		"struct type_%u* result = func_%u();"
	"", super->type->id, new_id);
	
	struct tuple_type* left_type = (void*) this->left->type;
	
	unsigned argcounter = 0;
	
	type_list_foreach(left_type->subtypes, ({
		void runme(struct type* subtype)
		{
			unsigned inc_id = function_queue_submit_inc(shared->fqueue, subtype);
			
			stringtree_append_printf(tree, "result->$%u = func_%u(left->$%u);", argcounter, inc_id, argcounter);
			
			argcounter++;
		}
		runme;
	}));
	
	struct tuple_type* right_type = (void*) this->right->type;
	
	unsigned right_argcounter = 0;
	type_list_foreach(right_type->subtypes, ({
		void runme(struct type* subtype)
		{
			unsigned inc_id = function_queue_submit_inc(shared->fqueue, subtype);
			
			stringtree_append_printf(tree, "result->$%u = func_%u(right->$%u);", argcounter++, inc_id, right_argcounter++);
		}
		runme;
	}));
	
	unsigned left_free_id = function_queue_submit_free(shared->fqueue, this->left->type);
	unsigned right_free_id = function_queue_submit_free(shared->fqueue, this->right->type);
	
	stringtree_append_printf(tree, "func_%u(left), func_%u(right);", left_free_id, right_free_id);
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(left), free_stringtree(right);
	
	EXIT;
	return tree;
}














