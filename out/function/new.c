
#include <debug.h>

#include "struct.h"
#include "new.h"

struct out_function* new_out_function(
	struct stringtree* text)
{
	ENTER;
	
	struct out_function* this = smalloc(sizeof(*this));
	
	this->rank = 0;
	this->dependent_on = new_ptrset();
	this->dependent_of = new_ptrset();
	this->text = inc_stringtree(text);
	
	EXIT;
	return this;
}
