
struct type;
struct type_lookup;

struct type_inheritance
{
	int (*compare)(
		const struct type*,
		const struct type*);
	
	struct stringtree* (*print_source)(
		struct type*,
		struct type_lookup* tlookup);
	
	void (*print)(
		struct type*);
	
	void (*free)(
		struct type*);
};

