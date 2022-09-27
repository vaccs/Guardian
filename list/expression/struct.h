
struct expression_list
{
	struct expression** data;
	unsigned n, cap;
	
	unsigned refcount;
};
