
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

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
		"static struct type_%u* func_%u(struct type_%u* val) {"
			"val->refcount++;"
			"return val;"
		"}"
	"", type_id, func_id, type_id);
	
	EXIT;
	return text;
}

