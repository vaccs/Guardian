
struct shared;
struct value;

struct value_inheritance
{
	int (*compare)(
		const struct value*,
		const struct value*);
	
	struct stringtree* (*print_source)(
		struct value*,
		struct out_shared* shared);
	
	void (*print)(struct value*);
	
	void (*free)(struct value*);
};

