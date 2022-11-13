
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
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	assert(super->kind == ek_dict_index);
	
	struct dict_index_expression* this = (void*) super;
	
	struct value* dict = expression_evaluate(this->dict, scope);
	
	struct value* index = expression_evaluate(this->index, scope);
	
	assert(dict->type->kind == tk_dict);
	
	assert(((struct dict_type*) dict->type)->key == index->type);
	
	struct value* value = dict_index_run((struct dict_value*) dict, index);
	
	free_value(dict), free_value(index);
	
	EXIT;
	return value;
}

























