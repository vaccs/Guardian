
struct function_queue;
struct type_queue;
struct type;
struct type_lookup;
struct out_shared;

struct type_inheritance
{
	int (*compare)(
		const struct type*,
		const struct type*);
	
	struct stringtree* (*generate_typedef)(
		struct type*,
		struct type_queue*);
	
	struct stringtree* (*generate_new_func)(
		struct type*,
		unsigned func_id,
		struct function_queue*);
	
	struct stringtree* (*generate_new_forward)(
		struct type*,
		unsigned func_id);
	
	struct stringtree* (*generate_inc_func)(
		struct type*);
	
	struct stringtree* (*generate_compare_func)(
		struct type*,
		unsigned,
		struct function_queue*);
	
	struct stringtree* (*generate_free_func)(
		struct type*,
		unsigned,
		struct function_queue*);
	
	void (*print)(
		struct type*);
	
	void (*free)(
		struct type*);
};

