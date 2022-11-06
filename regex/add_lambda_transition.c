
#include <debug.h>

#include <memory/srealloc.h>

#include "struct.h"
#include "add_lambda_transition.h"

void regex_add_lambda_transition(
	struct regex* this,
	struct regex* from)
{
	ENTER;
	
	if (this->lambdas.n == this->lambdas.cap)
	{
		this->lambdas.cap = this->lambdas.cap << 1 ?: 1;
		
		this->lambdas.data = srealloc(this->lambdas.data,
			sizeof(*this->lambdas.data) * this->lambdas.cap);
	}
	
	this->lambdas.data[this->lambdas.n++] = from;
	
	EXIT;
}

