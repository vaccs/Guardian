
#include <assert.h>

#include <debug.h>

#include "process_escapes.h"

void string_process_escapes(
	struct string* this)
{
	ENTER;
	
	TODO;
	#if 0
	assert(this->chars[0] == '\"');
	
	char *start = this->chars + 1;
	char *end = start + this->len - 2;
	
	char *read = start, *write = this->chars;
	
	while (read < end)
	{
		if (*read != '\\')
		{
			*write++ = *read++;
		}
		else
		{
			TODO;
		}
	}
	
	this->len = write - this->chars;
	
	dpvs(this);
	#endif
	
	EXIT;
}









