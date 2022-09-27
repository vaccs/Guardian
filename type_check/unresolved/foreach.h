
void unresolved_foreach(
	const struct unresolved* this,
	void (*runme)(struct string* name));
	
	
void unresolved_foreach2(
	const struct unresolved* this,
	void (*runme)(struct string* name, struct type* type, struct value* value));
	
	
