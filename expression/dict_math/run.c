
#include <debug.h>

#include <value/dict/struct.h>

#include "run.h"

struct value* dict_math_concat_run(
	struct type* type,
	struct dict_value* left,
	struct dict_value* right)
{
	ENTER;
	
	struct value_pair_list* leftlist = left->elements;
	struct value_pair_list* rightlist = right->elements;
	
	struct value_pair_list* concatlist = left->elements;
	
	
	TODO;
	
	EXIT;
}

