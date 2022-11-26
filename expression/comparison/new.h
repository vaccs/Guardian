
#include "kind.h"

struct expression* new_comparison_expression(
	struct type* type,
	enum comparison_expression_kind kind,
	struct expression* left,
	struct expression* right);
