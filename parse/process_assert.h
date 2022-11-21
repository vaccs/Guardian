
struct raw_statement_list;
struct zebu_assert_statement;

void process_assert(
	struct raw_statement_list* statements,
	struct zebu_assert_statement* zstatement);
