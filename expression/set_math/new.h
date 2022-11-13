
#include "kind.h"

struct type_cache;

struct expression* new_set_math_expression(
	struct type* type,
	enum set_math_expression_kind kind,
	struct expression* left,
	struct expression* right);
