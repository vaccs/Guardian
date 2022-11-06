
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_string_list(
	struct string_list* this)
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
		free_string(this->data[i]);
	
	free(this->data);
	free(this);
	
	EXIT;
}
