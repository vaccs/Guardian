
#include <debug.h>

#include "0.highest.h"
#include "1.prefix.h"

charset_t process_charset_prefix(
	struct zebu_charset_prefix* prefix)
{
	ENTER;
	
	charset_t base = process_charset_prefix(root->base);
	
	TODO;
	
	EXIT;
}

