
struct type;
struct function_queue;

struct stringtree* bool_type_generate_free_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup);
