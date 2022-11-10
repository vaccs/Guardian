
struct string;
struct scope;
struct value;

void scope_foreach(
	const struct scope* this,
	void (*runme)(struct string* name, struct value* value));
