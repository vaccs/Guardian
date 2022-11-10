
struct named_expression
{
	struct string* name;
	
	struct expression* expression;
	
	unsigned refcount;
};

