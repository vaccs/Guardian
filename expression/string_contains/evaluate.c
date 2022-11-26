
#include <assert.h>

#include <debug.h>

#include <value/struct.h>

#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* string_contains_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	assert(super->kind == ek_string_contains);
	
	struct string_contains_expression* this = (void*) super;
	
	struct value* substring = expression_evaluate(tcache, this->substring, environment);
	
	struct value* string = expression_evaluate(tcache, this->string, environment);
	
	assert(substring->kind == vk_string);
	
	assert(string->kind == vk_string);
	
	struct value* value = string_contains_run(
		super->type,
		(struct string_value*) substring,
		(struct string_value*) string);
	
	free_value(substring);
	
	free_value(string);
	
	EXIT;
	return value;
}
