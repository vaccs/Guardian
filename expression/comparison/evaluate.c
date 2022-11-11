
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
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	struct comparison_expression* this = (void*) super;
	
	struct value* left = expression_evaluate(this->left, scope);
	struct value* right = expression_evaluate(this->right, scope);
	
	assert(left->type == right->type);
	
	int cmp = compare_values(left, right);
	
	dpv(cmp);
	
	bool result;
	
	switch (this->kind)
	{
		case cek_equal_to:
			TODO;
			break;
		case cek_less_than: result = cmp < 0; break;
		case cek_greater_than:
			TODO;
			break;
		case cek_not_equal_to:
			TODO;
			break;
		case cek_less_than_equal_to:
			TODO;
			break;
		case cek_greater_than_equal_to:
			TODO;
			break;
		default:
			TODO;
			break;
	}
	
	dpvb(result);
	
	struct value* retval = new_bool_value(super->type, result);
	
	free_value(left), free_value(right);
	
	EXIT;
	return retval;
}













