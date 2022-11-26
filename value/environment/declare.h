
struct value;
struct string;

void environment_value_declare(
	struct value* this,
	struct string* name,
	struct value* value);
