
struct raw_assertion_list;
struct raw_assertion;

void raw_assertion_list_foreach(
	struct raw_assertion_list* this,
	void (*runme)(struct raw_assertion* this));