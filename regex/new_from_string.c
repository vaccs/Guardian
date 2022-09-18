
#include <debug.h>

#include "struct.h"
#include "new.h"
#include "new_from_string.h"

struct rbundle new_regex_from_string(
	const unsigned char* string,
	unsigned len)
{
	ENTER;
	
	dpvsn(string, len);
	
	assert(len);
	
	struct regex* start = new_regex();
	
	struct regex* accept = start;
	
	while (len--)
	{
		struct regex* temp = new_regex();
		
		accept->transitions[*string++] = temp;
		
		accept = temp;
	}
	
	EXIT;
	return (struct rbundle) {start, accept};
}

