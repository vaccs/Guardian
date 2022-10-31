
#include <string.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_strings(const void* a, const void* b)
{
	const struct string *A = a, *B = b;
	ENTER;
	
	dpvsn(A->chars, A->len);
	dpvsn(B->chars, B->len);
	
	EXIT;
	if (A->len > B->len)
		return +1;
	else if (A->len < B->len)
		return -1;
	else
		return strncmp(A->chars, B->chars, A->len);
}

