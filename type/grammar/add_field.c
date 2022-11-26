
#include <debug.h>

#include <named/type/new.h>
#include <named/type/free.h>

#include <list/named_type/append.h>

#include "struct.h"
#include "add_field.h"

void grammar_type_add_field(
	struct grammar_type* this,
	struct string* name,
	struct type* type)
{
	ENTER;
	
	struct named_type* field = new_named_type(name, type);
	
	named_type_list_append(this->fields, field);
	
	free_named_type(field);
	
	EXIT;
}

