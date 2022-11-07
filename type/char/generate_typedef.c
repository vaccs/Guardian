
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_typedef.h"

struct stringtree* char_type_generate_typedef(
	struct type* super,
	struct type_queue* tlookup)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, ""
		"struct type_%u {"
			"unsigned code;"
			"unsigned refcount;"
		"} ;"
	"", super->id);
	
	EXIT;
	return tree;
}

