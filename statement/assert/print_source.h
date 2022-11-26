
struct environment_type;
struct out_shared;
struct statement;

struct stringtree* assert_statement_print_source(
	struct statement* super,
	struct out_shared* shared,
	struct type* environment_type);
