
#include <stdbool.h>

struct type_check_scope;
struct string;
struct type;
struct value;

bool type_check_scope_lookup(
	struct type_check_scope* this,
	struct string* name,
	struct type** out_type,
	struct value** out_value);
