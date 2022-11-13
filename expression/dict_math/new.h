
#include "kind.h"

struct type_cache;

struct expression* new_dict_math_expression(
	struct type* type,
	enum dict_math_expression_kind kind,
	struct expression* left,
	struct expression* right);
