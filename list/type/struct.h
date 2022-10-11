
struct type_list
{
	struct type** data;
	unsigned n, cap;
	
	unsigned refcount;
};

