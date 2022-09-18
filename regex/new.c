
#include <debug.h>

#include "struct.h"
#include "new.h"

struct regex* new_regex()
{
	ENTER;
	
	struct regex* this = smalloc(sizeof(*this));
	
	memset(this->transitions, 0, sizeof(this->transitions));
	
	this->EOF_transition_to = NULL;
	
	this->lambdas.data = NULL;
	this->lambdas.n = 0;
	this->lambdas.cap = 0;
	
	this->kind = 0;
	
	this->accepts = 0;
	
	EXIT;
	return this;
}

