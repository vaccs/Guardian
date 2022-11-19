
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <type/print.h>

#include "struct.h"
#include "generate_print_func.h"

struct stringtree* lambda_type_generate_print_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_lambda);
	
	struct stringtree* text = new_stringtree();
	
	struct stringtree* type = type_print2(super);
	
	stringtree_append_printf(text, ""
		"void func_%u(struct type_%u* this)"
		"{"
			"printf(\"%%s\", \""
	"", func_id, super->id);
	
	stringtree_append_tree(text, type);
	
	stringtree_append_printf(text, ""
			"\");"
		"}"
	"");
	
	free_stringtree(type);
	
	EXIT;
	return text;
}

