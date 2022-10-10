
#include <debug.h>

#include "struct.h"
#include "generate_new_func.h"

struct stringtree* list_type_generate_new_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	unsigned type_id = super->id;
	
	assert(super->kind == tk_list);
	
	struct int_type* this = (void*) super;
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"static type_%u* func_%u() {"
			"type_%u* this = malloc(sizeof(*this));"
			"this->data = NULL;"
			"this->n = 0;"
			"this->cap = 0;"
			"this->refcount = 1;"
			"return this;"
		"}"
	"", type_id, func_id, type_id);
	
	EXIT;
	return text;
}

