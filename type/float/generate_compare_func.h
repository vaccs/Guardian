
struct type;
struct function_queue;

struct stringtree* float_type_generate_compare_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup);
