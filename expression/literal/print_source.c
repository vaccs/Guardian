
#include <debug.h>

/*#include <type/struct.h>*/

#include <value/print_source.h>

#include <misc/value_to_id/new.h>
#include <misc/value_to_id/free.h>

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
	
	struct value_to_id* vtoi = new_value_to_id();
	
	struct stringtree* tree = value_print_source(this->value, shared, vtoi);
	
	free_value_to_id(vtoi);
	
	EXIT;
	return tree;
}














