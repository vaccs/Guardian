
#include <debug.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* lambda_expression_print_source(
	struct expression* super,
	struct out_shared* shared)
{
	ENTER;
	
	assert(super->kind == ek_lambda);
	
	struct lambda_expression* this = (void*) super;
	
/*	struct parameter_list* parameters;*/
/*	*/
/*	struct parameter_list* captured;*/
/*	*/
/*	struct expression* body;*/
	
	struct stringtree* tree = new_stringtree();
	
	TODO;
	
	EXIT;
	return tree;
}

