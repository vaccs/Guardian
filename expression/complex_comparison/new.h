
#include "kind.h"

struct expression* new_complex_comparison_expression(
	struct type_cache *tcache,
	enum comparison_kind kind,
	struct expression* left,
	struct expression* right);
