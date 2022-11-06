
#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "generate_compare_forward.h"

struct stringtree* type_generate_compare_forward(
	struct type* this,
	unsigned func_id)
{
	ENTER;
	
	unsigned type_id = this->id;
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"auto int func_%u(const struct type_%u*, const struct type_%u*);"
	"", func_id, type_id, type_id);
	
	EXIT;
	return text;
}

