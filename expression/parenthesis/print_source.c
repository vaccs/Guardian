
#include <debug.h>

/*#include <type/struct.h>*/

/*#include <value/print_source.h>*/

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* parenthesis_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	struct parenthesis_expression* this = (void*) super;
	
	struct stringtree* tree = expression_print_source(this->expression, shared, environment);
	
	EXIT;
	return tree;
}














