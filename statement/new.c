
#include <debug.h>

#include <memory/smalloc.h>

#include <expression/inc.h>

#include <string/inc.h>

#include "struct.h"
#include "new.h"

struct statement* new_assert_statement(
	unsigned line,
	enum assertion_kind assertion_kind,
	struct expression* expression)
{
	ENTER;
	
	struct statement* this = smalloc(sizeof(*this));
	
	this->kind = sk_assertion;
	
	this->assertion_kind = assertion_kind;
	
	this->expression = inc_expression(expression);
	
	this->refcount = 1;
	
	this->line = line;
	
	EXIT;
	return this;
}

struct statement* new_declare_statement(
	struct string* name,
	struct expression* expression)
{
	ENTER;
	
	struct statement* this = smalloc(sizeof(*this));
	
	this->kind = sk_declaration;
	
	this->name = inc_string(name);
	
	this->expression = inc_expression(expression);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}


struct statement* new_print_statement(
	struct expression* expression)
{
	ENTER;
	
	struct statement* this = smalloc(sizeof(*this));
	
	this->kind = sk_print;
	
	this->expression = inc_expression(expression);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}












