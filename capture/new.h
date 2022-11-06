
#include <expression/variable/kind.h>

struct capture* new_capture(
	struct string* name,
	enum variable_expression_kind kind,
	struct type* type);
