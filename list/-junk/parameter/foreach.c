
#include <debug.h>

/*#include <parameter/struct.h>*/

#include "struct.h"
#include "foreach.h"

void parameter_list_foreach(
	struct parameter_list* this,
	void (*runme)(struct string* name, struct type* type))
{
	ENTER;
	
	TODO;
	#if 0
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		struct parameter* ele = this->data[i];
		
		runme(ele->name, ele->type);
	}
	#endif
	
	EXIT;
}

