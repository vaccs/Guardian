
struct value_list
{
	struct value** data;
	unsigned n, cap;
	
	unsigned refcount;
};

