
struct dict_value;
struct value;

void dict_value_foreach(
	struct dict_value* this,
	void (*runme)(
		struct value* key,
		struct value* value));
