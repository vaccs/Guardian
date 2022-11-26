
#include <stdbool.h>
#include <assert.h>

#include <debug.h>

#include <value/struct.h>
#include <value/compare.h>
#include <value/bool/new.h>
#include <value/free.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* comparison_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct comparison_expression* this = (void*) super;
	
	struct value* left = expression_evaluate(tcache, this->left, environment);
	
	struct value* right = expression_evaluate(tcache, this->right, environment);
	
	assert(left->type == right->type);
	
	int cmp = compare_values(left, right);
	
	dpv(cmp);
	
	bool result;
	
	switch (this->kind)
	{
		case cek_equal_to: result = cmp == 0; break;
		
		case cek_less_than: result = cmp < 0; break;
		
		case cek_greater_than: result = cmp > 0; break;
		
		case cek_not_equal_to: result = cmp != 0; break;
		
		case cek_less_than_equal_to: result = cmp <= 0; break;
		
		case cek_greater_than_equal_to: result = cmp >= 0; break;
		
		default: TODO; break;
	}
	
	dpvb(result);
	
	struct value* retval = new_bool_value(super->type, result);
	
	free_value(left), free_value(right);
	
	EXIT;
	return retval;
}













