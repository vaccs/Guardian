
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

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
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"static struct type_%u* func_%u() {"
			"struct type_%u* this = malloc(sizeof(*this));"
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

