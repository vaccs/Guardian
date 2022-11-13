
struct type;
struct string;
struct parameter_list;

void parameter_list_foreach(
	struct parameter_list* this,
	void (*runme)(
		struct string* name,
		struct type* type));
