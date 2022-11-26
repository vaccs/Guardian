
struct type;
struct environment_type;
struct expression;
struct scope;
struct value;
struct shared;
struct out_shared;
struct type_cache* tcache;

struct expression_inheritance
{
	struct value* (*evaluate)(
		struct type_cache*,
		struct expression*,
		struct value*);
	
	struct stringtree* (*print_source)(
		struct expression*,
		struct out_shared*,
		struct type*);
	
	struct stringtree* (*print)(
		struct expression*);
		
	void (*free)(
		struct expression*);
};

