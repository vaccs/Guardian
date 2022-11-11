
struct environment_type;
struct expression;
struct scope;
struct value;
struct shared;
struct out_shared;

struct expression_inheritance
{
	struct value* (*evaluate)(
		struct expression*,
		struct scope*);
	
	struct stringtree* (*print_source)(
		struct expression*,
		struct out_shared*,
		struct environment_type*);
	
	void (*print)(
		struct expression*);
		
	void (*free)(
		struct expression*);
};

