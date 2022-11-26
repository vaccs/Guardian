
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_new_func.h"

struct stringtree* string_type_generate_new_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_string);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"struct type_%u* func_%u(unsigned char* chars, unsigned len) {"
			"struct type_%u* this = malloc(sizeof(*this));"
			"this->chars = chars;"
			"this->len = len;"
			"this->refcount = 1;"
			"return this;"
		"}"
	"", super->id, func_id, super->id);
	
	EXIT;
	return text;
}

