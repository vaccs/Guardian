
struct expression_pair
{
	struct expression* key;
	struct expression* value;
	
	unsigned refcount;
};

