
struct type;
struct type_lookup;
struct out_shared;

struct type_inheritance
{
	int (*compare)(
		const struct type*,
		const struct type*);
	
	struct stringtree* (*generate_new_text)(
		struct type*,
		unsigned func_id,
		struct function_lookup*);
	
	struct stringtree* (*generate_typedef_text)(
		struct type*,
		struct type_lookup*);
	
	struct stringtree* (*generate_inc_text)(
		struct type*);
	
	struct stringtree* (*generate_compare_text)(
		struct type*,
		unsigned,
		struct function_lookup*);
	
	struct stringtree* (*generate_free_text)(
		struct type*,
		unsigned,
		struct function_lookup*);
	
	void (*print)(
		struct type*);
	
	void (*free)(
		struct type*);
};

