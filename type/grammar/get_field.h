
struct grammar_type;
struct string;

struct type* grammar_type_get_field(
	struct grammar_type* this,
	struct string* fieldname);
