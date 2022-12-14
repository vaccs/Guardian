
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

/*#include <value/struct.h>*/
/*#include <value/integer/new.h>*/
#include <type/dict/struct.h>

#include <value/struct.h>
/*#include <value/dict/lookup.h>*/
#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* dict_index_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	assert(super->kind == ek_dict_index);
	
	struct dict_index_expression* this = (void*) super;
	
	struct value* dict = expression_evaluate(tcache, this->dict, environment);
	
	struct value* index = expression_evaluate(tcache, this->index, environment);
	
	assert(dict->type->kind == tk_dict);
	
	assert(((struct dict_type*) dict->type)->key == index->type);
	
	struct value* value = dict_index_run((struct dict_value*) dict, index);
	
	free_value(dict), free_value(index);
	
	EXIT;
	return value;
}

























