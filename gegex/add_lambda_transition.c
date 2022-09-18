
#include <debug.h>

#include "struct.h"
#include "add_lambda_transition.h"

void gegex_add_lambda_transition(
	struct gegex* this,
	struct gegex* to)
{
	ENTER;
	
	if (this->lambdas.n == this->lambdas.cap)
	{
		this->lambdas.cap = this->lambdas.cap << 1 ?: 1;
		
		this->lambdas.data = srealloc(this->lambdas.data,
			sizeof(*this->lambdas.data) * this->lambdas.cap);
	}
	
	this->lambdas.data[this->lambdas.n++] = to;
	
	EXIT;
}

