
struct type;
struct function_queue;

struct stringtree* char_type_generate_new_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup);
