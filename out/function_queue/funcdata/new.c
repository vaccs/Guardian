
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct funcdata* new_funcdata(
	enum funcdata_kind kind,
	struct type* type,
	struct lambda_expression* lexpression,
	struct lambda_value* lvalue,
	unsigned id)
{
	ENTER;
	
	struct funcdata* this = smalloc(sizeof(*this));
	
	this->kind = kind;
	
	this->type = type;
	
	this->lexpression = lexpression;
	
	this->lvalue = lvalue;
	
	this->id = id;
	
	EXIT;
	return this;
}

