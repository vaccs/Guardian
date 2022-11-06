
#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include <parse/parse.h>

#include "struct.h"
#include "new.h"

struct named_zebu_type* new_named_zebu_type(
	struct string* name,
	struct zebu_type* type)
{
	ENTER;
	
	struct named_zebu_type* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->type = inc_zebu_type(type);
	
	EXIT;
	return this;
}


