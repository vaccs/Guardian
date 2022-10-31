
#include <debug.h>

#include "struct.h"
#include "generate_inc_func.h"

struct stringtree* type_generate_inc_func(
	struct type* this,
	unsigned func_id)
{
	ENTER;
	
	unsigned type_id = this->id;
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"static type_%u* func_%u(type_%u* val) {"
			"return val->refcount++, val;"
		"}"
	"", type_id, func_id, type_id);
	
	EXIT;
	return text;
}

