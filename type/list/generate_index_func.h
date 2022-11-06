
struct list_type;
struct out_shared;

struct stringtree* list_type_generate_index_func(
	struct list_type* this,
	unsigned func_id,
	struct out_shared* shared);
