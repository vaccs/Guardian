
#include <stddef.h>

#include "kind.h"

struct expression_inheritance;
struct type;

struct expression* new_expression(
	enum expression_kind kind,
	struct expression_inheritance* inheritance,
	struct type* type,
	size_t alloc_size);
