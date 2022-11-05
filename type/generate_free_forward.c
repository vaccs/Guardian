
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_free_forward.h"

struct stringtree* type_generate_free_forward(
	struct type* this,
	unsigned func_id)
{
	ENTER;
	
	unsigned type_id = this->id;
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"static void func_%u(struct type_%u*);"
	"", func_id, type_id);
	
	EXIT;
	return text;
}

