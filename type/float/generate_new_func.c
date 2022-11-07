
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_new_func.h"

struct stringtree* float_type_generate_new_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_float);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"struct type_%u* func_%u(long double value) {"
			"struct type_%u* this = malloc(sizeof(*this));"
			"this->value = value;"
			"this->refcount = 1;"
			"return this;"
		"}"
	"", super->id, func_id, super->id);
	
	EXIT;
	return text;
}













