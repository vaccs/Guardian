
#include <expression/variable/kind.h>

void unresolved_resolve(
	struct unresolved* this,
	struct string* name,
	enum variable_expression_kind kind,
	struct type* type,
	struct value* value);
