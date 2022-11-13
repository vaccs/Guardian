
#include <debug.h>

/*#include <type/struct.h>*/

#include <value/print_source.h>

/*#include "../print_source.h"*/

#include "struct.h"
#include "print_source.h"

struct stringtree* literal_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	struct literal_expression* this = (void*) super;
	
	struct stringtree* tree = value_print_source(this->value, shared);
	
	EXIT;
	return tree;
}














