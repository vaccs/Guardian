
#include <debug.h>

#include "struct.h"
#include "new.h"
#include "new_from_charset.h"

struct rbundle new_regex_from_charset(charset_t charset)
{
	ENTER;
	
	struct regex* start = new_regex();
	struct regex* accept = new_regex();
	
	for (unsigned i = 0, n = 256; i < n; i++)
		if (charset[i >> 4] & 1 << (i & 0xF))
			start->transitions[i] = accept;
	
	EXIT;
	return (struct rbundle) {start, accept};
}

