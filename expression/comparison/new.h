
#include "kind.h"

struct type_cache;

struct expression* new_comparison_expression(
	struct type_cache *tcache,
	enum comparison_expression_kind kind,
	struct expression* left,
	struct expression* right);
