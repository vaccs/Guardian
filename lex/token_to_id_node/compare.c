
#include <debug.h>

#include <regex/compare_simplified.h>

#include "struct.h"
#include "compare.h"

int compare_token_to_id_nodes(const void* a, const void* b)
{
	const struct token_to_id_node *A = a, *B = b;
	ENTER;
	
	int cmp = regex_compare_simplified(A->token, B->token);
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}

