
struct out_shared;
struct stringtree;
struct statement;
struct environment_type;
struct expression;

struct statement_inheritance
{
	struct stringtree* (*print_source)(
		struct statement* statement,
		struct out_shared* shared,
		struct environment_type* environment_type);
	
	void (*free)(
		struct statement* statement);
	
};

