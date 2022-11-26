
#include "../struct.h"

struct string_value
{
	struct value super;
	
	unsigned char* chars;
	
	unsigned len;
	
};

