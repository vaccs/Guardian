
#include <assert.h>

#include <debug.h>

#include <value/struct.h>
#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* dict_contains_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	assert(super->kind == ek_dict_contains);
	
	struct dict_contains_expression* this = (void*) super;
	
	struct value* key = expression_evaluate(tcache, this->key, environment);
	
	struct value* dict = expression_evaluate(tcache, this->dict, environment);
	
	assert(dict->kind == vk_dict);
	
	struct value* value = dict_contains_run(
		super->type,
		(struct value*) key,
		(struct dict_value*) dict);
	
	free_value(key);
	
	free_value(dict);
	
	EXIT;
	return value;
}
