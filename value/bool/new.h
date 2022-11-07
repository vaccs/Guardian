
#include <stdbool.h>

struct type_cache;

struct value* new_bool_value(
	struct type_cache* tcache,
	bool value);

