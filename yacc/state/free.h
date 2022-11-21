
struct ptrset;
struct quack;
struct yacc_state;

void free_yacc_state_loop(
	struct ptrset* yacc_queued,
	struct ptrset* lex_queued,
	struct quack* todo);

void free_yacc_state(struct yacc_state* this);
