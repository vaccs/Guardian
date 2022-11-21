
struct type;
struct type_check_scope;
struct value;

void type_check_scope_declare(
	struct type_check_scope* this,
	struct string* name,
	struct type* type);

void type_check_scope_declare_value(
	struct type_check_scope* this,
	struct string* name,
	struct value* value);
