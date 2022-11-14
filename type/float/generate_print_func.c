
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_print_func.h"

struct stringtree* float_type_generate_print_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_float);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"void func_%u(struct type_%u* this)"
		"{"
			"printf(\"%%Lg\", this->value);"
		"}"
	"", func_id, super->id);
	
	EXIT;
	return text;
}













