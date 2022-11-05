
#include <stdbool.h>

struct string;

bool stringset_contains(
	const struct stringset* this,
	struct string* element);
