
struct named_type_list
{
	struct named_type** data;
	
	unsigned n, cap;
	
	unsigned refcount;
};

