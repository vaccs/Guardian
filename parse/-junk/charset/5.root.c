
#include <debug.h>

#include "4.symdiff.h"
#include "5.root.h"

charset_t process_charset_root(
	struct zebu_charset* root)
{
	ENTER;
	
	charset_t base = process_charset_symdiff(root->base);
	
	TODO;
	
	EXIT;
}

