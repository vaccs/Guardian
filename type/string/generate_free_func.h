
struct type;
struct function_queue;

struct stringtree* string_type_generate_free_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup);
