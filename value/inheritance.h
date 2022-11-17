
struct value_to_id;
struct environment_type;
struct out_shared;
struct shared;
struct value;

struct value_inheritance
{
	int (*compare)(
		const struct value*,
		const struct value*);
	
	struct stringtree* (*print_source)(
		struct value*,
		struct out_shared* shared,
		struct value_to_id* vtoi);
	
	struct stringtree* (*print)(struct value*);
	
	void (*free)(struct value*);
};

