
struct ptrset;
struct quack;
struct yacc_state;
struct statement_list;

void free_yacc_state(struct yacc_state* this);

void free_all_yacc_states(struct statement_list* statements);
