
#include <stdbool.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

/*#include <list/type/foreach.h>*/

/*#include <out/function_queue/submit_inc.h>*/

#include "struct.h"
#include "generate_new_forward.h"

struct stringtree* tuple_type_generate_new_forward(
	struct type* super,
	unsigned func_id)
{
	ENTER;
	
	assert(super->kind == tk_tuple);
	
	struct stringtree* text = new_stringtree();
	
/*	struct tuple_type* this = (void*) super;*/
	
	stringtree_append_printf(text, ""
		"auto struct type_%u* func_%u();"
	"", super->id, func_id);
	
	EXIT;
	return text;
}













