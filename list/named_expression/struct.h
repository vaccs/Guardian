
struct named_expression_list
{
	struct named_expression** data;
	
	unsigned n, cap;
	
	unsigned refcount;
};

