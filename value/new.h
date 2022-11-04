
#include <stddef.h>

enum value_kind;
struct type;
struct value_inheritance;

struct value* new_value(
	struct type* type,
	enum value_kind kind,
	struct value_inheritance* inheritance,
	size_t alloc_size);
