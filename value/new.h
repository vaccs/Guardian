
struct value_inheritance;

struct value* new_value(
	struct type* type,
	struct value_inheritance* inheritance,
	size_t alloc_size);
