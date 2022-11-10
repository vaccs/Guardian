
struct value_pair_list;
struct value_pair;

void value_pair_list_qsort(
	struct value_pair_list* this,
	int (*compare)(const struct value_pair* a, const struct value_pair* b));
