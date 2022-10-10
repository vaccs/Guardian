
#include <debug.h>

#include <set/ptr/new.h>

#include <stringtree/inc.h>

#include "struct.h"
#include "new.h"

struct out_type* new_out_type(
	struct stringtree* text)
{
	ENTER;
	
	struct out_type* this = smalloc(sizeof(*this));
	
	this->rank = 0;
	this->dependent_on = new_ptrset();
	this->dependent_of = new_ptrset();
	this->text = inc_stringtree(text);
	
	EXIT;
	return this;
}

