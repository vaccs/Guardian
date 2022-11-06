
#include <stdbool.h>

struct ptrset;

bool ptrset_contains(
	const struct ptrset* this,
	const void* element);
	
