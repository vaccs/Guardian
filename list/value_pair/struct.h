
struct value_pair_list
{
	struct value_pair** data;
	unsigned n, cap;
	
	unsigned refcount;
};
