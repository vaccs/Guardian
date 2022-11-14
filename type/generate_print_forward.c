
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "inheritance.h"
#include "struct.h"
#include "generate_print_forward.h"

struct stringtree* type_generate_print_forward(
	struct type* this,
	unsigned func_id)
{
	ENTER;
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"auto void func_%u(const struct type_%u*);"
	"", func_id, this->id);
	
	EXIT;
	return text;
}

