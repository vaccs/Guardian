
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_new_forward.h"

struct stringtree* environment_type_generate_new_forward(
	struct type* super,
	unsigned func_id)
{
	ENTER;
	
	TODO;
	#if 0
	unsigned type_id = super->id;
	
	assert(super->kind == tk_environment);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"auto struct type_%u* func_%u(environment value);"
	"", type_id, func_id);
	
	EXIT;
	return text;
	#endif
}

