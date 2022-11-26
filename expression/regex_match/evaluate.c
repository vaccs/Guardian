
#include <assert.h>

#include <debug.h>

#include <value/struct.h>

#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* regex_match_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	assert(super->kind == ek_regex_match);
	
	struct regex_match_expression* this = (void*) super;
	
	struct value* string = expression_evaluate(tcache, this->string, environment);
	
	assert(string->kind == vk_string);
	
	struct value* result = regex_match_run(
		super->type, (struct string_value*) string, this->regex);
	
	free_value(string);
	
	EXIT;
	return result;
}
