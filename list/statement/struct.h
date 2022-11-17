
struct statement_list
{
	struct statement** data;
	unsigned n, cap;
	
	unsigned refcount;
};
