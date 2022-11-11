
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <set/string/free.h>

#include "struct.h"
#include "pop.h"
#include "free.h"

void free_type_check_scope(
	struct type_check_scope* this)
{
	ENTER;
	
	while (this->head)
	{
		type_check_scope_pop(this);
	}
	
	free_stringset(this->grammar_sets);
	
	free(this);
	
	EXIT;
}

