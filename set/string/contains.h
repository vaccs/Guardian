
#include <stdbool.h>

struct stringset;
struct string;

bool stringset_contains(
	const struct stringset* this,
	struct string* element);
