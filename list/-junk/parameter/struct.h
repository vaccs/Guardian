
struct parameter_list
{
	struct parameter** data;
	unsigned n, cap;
	
	unsigned refcount;
};

