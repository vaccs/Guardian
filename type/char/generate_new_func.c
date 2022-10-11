
#include <debug.h>

#include "struct.h"
#include "generate_new_func.h"

struct stringtree* char_type_generate_new_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	TODO;
	#if 0
	unsigned type_id = super->id;
	
	assert(super->kind == tk_int);
	
	struct int_type* this = (void*) super;
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"static type_%u* func_%u() {"
			"type_%u* this = malloc(sizeof(*this));"
			"mpz_init(this->value);"
			"this->refcount = 1;"
			"return this;"
		"}"
	"", type_id, func_id, type_id);
	
	EXIT;
	return text;
	#endif
}

