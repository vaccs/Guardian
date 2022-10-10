
#include <debug.h>

#include "struct.h"
#include "generate_new_func.h"

struct stringtree* bool_type_generate_new_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	unsigned type_id = super->id;
	
	assert(super->kind == tk_bool);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"static type_%u* func_%u(bool value) {"
			"type_%u* this = malloc(sizeof(*this));"
			"this->value = value;"
			"this->refcount = 1;"
			"return this;"
		"}"
	"", type_id, func_id, type_id);
	
	EXIT;
	return text;
}

