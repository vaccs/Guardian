
#include "kind.h"

struct type_cache;

struct expression* new_float_math_expression(
	struct type_cache *tcache,
	enum float_math_expression_kind kind,
	struct expression* left,
	struct expression* right);
