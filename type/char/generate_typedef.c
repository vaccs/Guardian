
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
	
	TODO;
	#if 0
	struct stringtree* tree = new_stringtree();
	
	dpv(super->id);
	
	stringtree_append_printf(tree, ""
		"typedef struct {"
			"mpz_t value;"
			"unsigned refcount;"
		"} type_%u;"
	"", super->id);
	
	EXIT;
	return tree;
	#endif
}

