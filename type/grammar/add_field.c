
#include <debug.h>

#include <parameter/new.h>
#include <parameter/free.h>

#include <list/parameter/append.h>

#include "struct.h"
#include "add_field.h"

void grammar_type_add_field(
	struct grammar_type* this,
	struct string* name,
	struct type* type)
{
	ENTER;
	
	struct parameter* field = new_parameter(name, type);
	
	parameter_list_append(this->fields, field);
	
	free_parameter(field);
	
	EXIT;
}

