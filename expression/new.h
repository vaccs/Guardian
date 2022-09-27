
struct expression_inheritance;

#include "kind.h"

struct expression* new_expression(
	enum expression_kind kind,
	struct expression_inheritance* inheritance,
	struct type* type,
	size_t alloc_size);
