
struct statement;
struct environment_type;
struct out_shared;

struct stringtree* parse_statement_print_source(
	struct statement* super,
	struct out_shared* shared,
	struct environment_type* environment_type);
