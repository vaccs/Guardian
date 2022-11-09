
struct string;
struct type;
struct value;

struct type_check_scope_node
{
	struct string* name;
	
	struct type* type;
	
	struct value* value;
};

