
#include "kind.h"

struct expression* new_primitive_comparision_expression(
	struct type_cache *tcache,
	enum comparison_kind kind,
	struct expression* left,
	struct expression* right);
