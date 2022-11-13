
struct value_pair
{
	struct value* key;
	struct value* value;
	
	unsigned refcount;
};

