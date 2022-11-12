
#include <assert.h>

#include <debug.h>

/*#include <type/struct.h>*/

/*#include <string/struct.h>*/

#include <stringtree/new.h>
/*#include <stringtree/append_tree.h>*/
#include <stringtree/append_printf.h>

/*#include <set/string/add.h>*/

/*#include <quack/append.h>*/

/*#include <type_cache/get_type/bool.h>*/

/*#include <out/shared.h>*/
/*#include <out/function_lookup/lookup_inc.h>*/
/*#include <out/declare_queue/submit.h>*/
/*#include <out/set_queue/submit.h>*/
/*#include <out/type_queue/submit.h>*/
/*#include <out/function_queue/submit_free.h>*/

/*#include <type/struct.h>*/

/*#include "../print_source.h"*/

#include "struct.h"
#include "print_source.h"

struct stringtree* dict_math_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	assert(super->kind == ek_dict_math);
	
	struct stringtree* tree = new_stringtree();
	
/*	struct dict_math_expression* this = (void*) super;*/
	
	stringtree_append_printf(tree, "({"
		"assert(!\"TODO: dict-concat\");"
		"NULL;"
	"})");
	
	#if 0
	type_queue_submit(shared->tqueue, super->type);
	
	struct type* btype = type_cache_get_bool_type(shared->tcache);
	
	type_queue_submit(shared->tqueue, btype);
	
	stringtree_append_printf(tree, ""
		"({"
	"");
	
	struct stringtree* left_text = expression_print_source(this->left, shared);
	
	stringtree_append_printf(tree, ""
			"struct type_%u* result = "
	"", btype->id);
	stringtree_append_tree(tree, left_text);
	stringtree_append_printf(tree, ";");
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, btype);
	
	stringtree_append_printf(tree, ""
			"if (!result->value)"
			"{"
				"func_%u(result);"
				"result = "
	"", free_id);
	
	struct stringtree* right_text = expression_print_source(this->right, shared);
	
	stringtree_append_tree(tree, right_text);
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, ""
			"}"
			"result;"
		"})"
	"");
	#endif
	
	EXIT;
	return tree;
}



































