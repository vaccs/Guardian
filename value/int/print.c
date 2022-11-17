
#include <stdlib.h>
#include <assert.h>
#include <gmp.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "print.h"

struct stringtree* int_value_print(
	struct value* super)
{
	ENTER;
	
	struct int_value* spef = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	char* buffer = NULL;
	
	int len = gmp_asprintf(&buffer, "%Zi", spef->value);
	
	if (len < 0)
	{
		TODO;
		exit(1);
	}
	
	dpvs(buffer);
	
	stringtree_append_printf(tree, "%s", buffer);
	
	free(buffer);
	
	EXIT;
	return tree;
}

