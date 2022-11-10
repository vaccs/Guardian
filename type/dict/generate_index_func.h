
struct dict_type;
struct out_shared;

struct stringtree* dict_type_generate_index_func(
	struct dict_type* this,
	unsigned func_id,
	struct out_shared* shared);
