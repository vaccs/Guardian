
#include <debug.h>

#include "3.intersect.h"
#include "4.symdiff.h"

charset_t process_charset_symdiff(
	struct zebu_charset_symdiff* symdiff)
{
	ENTER;
	
	charset_t base = process_charset_intersect(symdiff->base);
	
	TODO;
	
	EXIT;
}

