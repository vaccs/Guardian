
struct expression;
struct scope;
struct value;
struct shared;

struct expression_inheritance
{
	struct value* (*evaluate)(
		struct expression*,
		struct scope*);
	
	struct stringtree* (*print_source)(
		struct expression*,
		struct out_shared*);
	
	void (*print)(
		struct expression*);
		
	void (*free)(
		struct expression*);
};

