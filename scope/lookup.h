
struct string;
struct scope;

struct value* scope_lookup(
	struct scope* this,
	struct string* name);
