
#include <debug.h>

#include "1.prefix.h"
#include "2.range.h"

charset_t process_charset_range(
	struct zebu_charset_range* range)
{
	ENTER;
	
	charset_t base = process_charset_prefix(root->base);
	
	TODO;
	
	EXIT;
}

