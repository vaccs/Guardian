
#include <expression/variable/kind.h>

void unresolved_resolve_type(
	struct unresolved* this,
	struct string* name,
	enum variable_expression_kind kind,
	struct type* type);
	
void unresolved_resolve_value(
	struct unresolved* this,
	struct string* name,
	struct value* value);
