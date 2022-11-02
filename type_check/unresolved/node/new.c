
#include <debug.h>

#include <set/zpexpression/new.h>
#include <set/zpexpression/add.h>

#include "struct.h"
#include "new.h"

struct unresolved_node* new_unresolved_node(
	struct string* name,
	struct zebu_primary_expression* expression)
{
	ENTER;
	
	struct unresolved_node* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->layers.current = new_zpexpressionset();
	this->layers.deeper = new_zpexpressionset();
	
	zpexpressionset_add(this->layers.current, expression);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

