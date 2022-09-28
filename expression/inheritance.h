
struct expression;
struct scope;
struct value;

struct expression_inheritance
{
	struct value* (*evaluate)(
		struct expression*,
		struct scope*);
	
	void (*print)(
		struct expression*);
		
	void (*free)(
		struct expression*);
};

