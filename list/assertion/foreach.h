
struct assertion_list;

void assertion_list_foreach(
	struct assertion_list* this,
	void (*runme)(struct assertion* this));
