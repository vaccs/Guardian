
#include <assert.h>

#include <debug.h>

#include <value/struct.h>
#include <value/bool/struct.h>
/*#include <value/int/new.h>*/
#include <value/free.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* ternary_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	assert(super->kind == ek_ternary);
	
	struct ternary_expression* this = (void*) super;
	
	struct value* conditional = expression_evaluate(tcache, this->conditional, environment);
	
	assert(conditional->kind == vk_bool);
	
	struct bool_value* spef = (void*) conditional;
	
	struct value* result =
		expression_evaluate(tcache, spef->value ? this->true_case : this->false_case, environment);
	
	free_value(conditional);
	
	EXIT;
	return result;
}













