
struct statement;
struct type;

struct stringtree* statement_print_source(
	struct statement* this,
	struct out_shared* shared,
	struct type* environment_type);
