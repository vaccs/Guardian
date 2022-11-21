
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_compare_func.h"

struct stringtree* char_type_generate_compare_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_char);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"int func_%u(const struct type_%u* a, const struct type_%u* b)"
		"{"
			"if (a->value > b->value)"
			"{"
				"return +1;"
			"}"
			"else if (a->value < b->value)"
			"{"
				"return -1;"
			"}"
			"else"
			"{"
				"return +0;"
			"}"
		"}"
	"", func_id, super->id, super->id);
	
	EXIT;
	return text;
}

