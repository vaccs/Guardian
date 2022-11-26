
struct value_to_id;
struct value;

void value_to_id_foreach(
	struct value_to_id* this,
	void (*runme)(unsigned, struct value*));
