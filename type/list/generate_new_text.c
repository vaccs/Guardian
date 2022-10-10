
#include <debug.h>

#include "struct.h"
#include "generate_new_text.h"

struct stringtree* list_type_generate_new_text(
	struct type* super,
	unsigned func_id,
	struct function_lookup* flookup)
{
	ENTER;
	
	unsigned type_id = super->id;
	
	assert(super->kind == tk_list);
	
	struct int_type* this = (void*) super;
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"type_%u* func_%u() {"
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

