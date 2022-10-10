
#include "kind.h"

struct expression* new_variable_expression(
	struct type* type,
	enum variable_expression_kind kind,
	struct string* name);
