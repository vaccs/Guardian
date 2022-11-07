
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
/*#include <stringtree/append_prfloatf.h>*/

#include "struct.h"
#include "generate_new_forward.h"

struct stringtree* float_type_generate_new_forward(
	struct type* super,
	unsigned func_id)
{
	ENTER;
	
	TODO;
	#if 0
	unsigned type_id = super->id;
	
	assert(super->kind == tk_float);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_prfloatf(text, ""
		"auto struct type_%u* func_%u();"
	"", type_id, func_id);
	
	EXIT;
	return text;
	#endif
}

