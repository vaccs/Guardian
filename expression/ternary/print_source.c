
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

struct stringtree* ternary_expression_print_source(
	struct expression* super,
	struct out_shared* shared)
{
	ENTER;
	
	assert(super->kind == ek_ternary);
	
	struct ternary_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	struct type* rtype = super->type;
	
	type_queue_submit(shared->tqueue, rtype);
	
	struct type* btype = this->conditional->type;
	
	type_queue_submit(shared->tqueue, btype);
	
	stringtree_append_printf(tree, ""
		"({"
			"struct type_%u* conditional = "
	"", btype->id);
	
	struct stringtree* conditional = expression_print_source(this->conditional, shared);
	
	stringtree_append_tree(tree, conditional);
	
	stringtree_append_printf(tree, ""
		";"
	"");
	
	stringtree_append_printf(tree, ""
		"struct type_%u* result = conditional->value ? ("
	"", rtype->id);
	
	struct stringtree* true_case = expression_print_source(this->true_case, shared);
	
	stringtree_append_tree(tree, true_case);
	
	stringtree_append_printf(tree, ") : (");
	
	struct stringtree* false_case = expression_print_source(this->false_case, shared);
	
	stringtree_append_tree(tree, false_case);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, btype);
	
	stringtree_append_printf(tree, ""
				");"
			"func_%u(conditional);"
			"result;"
		"})"
	"", free_id);
	
	free_stringtree(conditional);
	free_stringtree(true_case);
	free_stringtree(false_case);
	
	EXIT;
	return tree;
}














