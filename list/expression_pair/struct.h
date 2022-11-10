
struct expression_pair_list
{
	struct expression_pair** data;
	unsigned n, cap;
	
	unsigned refcount;
};
