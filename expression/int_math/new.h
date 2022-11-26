
#include "kind.h"

struct type_cache;
struct type;

struct expression* new_int_math_expression(
	struct type* type,
	enum int_math_expression_kind kind,
	struct expression* left,
	struct expression* right);
