
#include <assert.h>

#include <debug.h>

#include <avl/insert.h>

#include <named/value/new.h>

#include "struct.h"
#include "declare.h"

void environment_value_declare(
	struct value* super,
	struct string* name,
	struct value* value)
{
	ENTER;
	
	assert(super->kind == vk_environment);
	
	struct environment_value* this = (void*) super;
	
	struct named_value* nvalue = new_named_value(name, value);
	
	void* ptr = avl_insert(this->variables, nvalue);
	
	assert(ptr);
	
	EXIT;
}

