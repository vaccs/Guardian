
struct zebu_expression_list
{
	struct zebu_expression** data;
	unsigned n, cap;
	
	unsigned refcount;
};
