
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "qsort.h"

void value_pair_list_qsort(
	struct value_pair_list* this,
	int (*compare)(const struct value_pair* a, const struct value_pair* b))
{
	ENTER;
	
	qsort(
		/* base: */ this->data,
		/* nmemb: */ this->n,
		/* size: */ sizeof(*this->data),
		/* compar: */ ({
			int compar(const void* a, const void* b)
			{
				const struct value_pair* const* A = a, * const* B = b;
				return compare(*A, *B);
			}
			compar;
		})
	);
	
	EXIT;
}

