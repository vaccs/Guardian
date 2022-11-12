
struct set_type;
struct out_shared;

struct stringtree* set_type_generate_index_func(
	struct set_type* this,
	unsigned func_id,
	struct out_shared* shared);
