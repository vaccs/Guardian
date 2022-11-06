
#include <stdbool.h>

struct stringset;
struct string;

bool stringset_add(
	struct stringset* this,
	struct string* string);
