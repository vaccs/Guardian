
struct string;
struct expression;

struct expression* new_fieldaccess_expression(
	struct type* type,
	struct expression* object,
	struct string* fieldname);
