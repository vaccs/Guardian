
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
		struct shared*);
	
	void (*print)(
		struct expression*);
		
	void (*free)(
		struct expression*);
};

