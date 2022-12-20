
#include <stdio.h>

struct zebu_token
{
	unsigned char* data;
	unsigned len, refcount, line;
};

struct zebu_$start
{
	struct {
		struct zebu_statement** data;
		unsigned n, cap;
	} statements;
	unsigned refcount, startline, endline;
};

struct zebu_0$keyvalue
{
	struct zebu_expression* key;
	struct zebu_expression* value;
	unsigned refcount, startline, endline;
};

struct zebu_1$parameter
{
	struct zebu_token* name;
	struct zebu_primitive_type* type;
	unsigned refcount, startline, endline;
};

struct zebu_2$parameter
{
	struct zebu_expression* expression;
	struct zebu_token* name;
	unsigned refcount, startline, endline;
};

struct zebu_additive_expression
{
	struct zebu_token* add;
	struct zebu_multiplicative_expression* base;
	struct zebu_additive_expression* left;
	struct zebu_multiplicative_expression* right;
	struct zebu_token* sub;
	unsigned refcount, startline, endline;
};

struct zebu_and_expression
{
	struct zebu_match_expression* base;
	struct zebu_and_expression* left;
	struct zebu_match_expression* right;
	unsigned refcount, startline, endline;
};

struct zebu_assert_statement
{
	struct zebu_token* error;
	struct zebu_expression* expression;
	struct zebu_token* note;
	struct zebu_token* warning;
	unsigned refcount, startline, endline;
};

struct zebu_charset
{
	struct zebu_charset_symdiff* base;
	struct {
		struct zebu_charset_symdiff** data;
		unsigned n, cap;
	} ors;
	unsigned refcount, startline, endline;
};

struct zebu_charset_highest
{
	struct zebu_token* character;
	struct zebu_token* integer;
	struct zebu_charset* subcharset;
	unsigned refcount, startline, endline;
};

struct zebu_charset_intersect
{
	struct zebu_charset_range* base;
	struct {
		struct zebu_charset_range** data;
		unsigned n, cap;
	} intersects;
	unsigned refcount, startline, endline;
};

struct zebu_charset_prefix
{
	struct zebu_charset_highest* base;
	struct zebu_token* emark;
	unsigned refcount, startline, endline;
};

struct zebu_charset_range
{
	struct zebu_charset_prefix* left;
	struct zebu_charset_prefix* right;
	unsigned refcount, startline, endline;
};

struct zebu_charset_symdiff
{
	struct zebu_charset_intersect* base;
	struct {
		struct zebu_charset_intersect** data;
		unsigned n, cap;
	} xors;
	unsigned refcount, startline, endline;
};

struct zebu_conditional_expression
{
	struct zebu_implication_expression* base;
	struct zebu_conditional_expression* false_case;
	struct zebu_token* qmark;
	struct zebu_expression* true_case;
	unsigned refcount, startline, endline;
};

struct zebu_declare_statement
{
	struct zebu_expression* expression;
	struct zebu_token* name;
	unsigned refcount, startline, endline;
};

struct zebu_equality_expression
{
	struct zebu_relational_expression* base;
	struct zebu_token* e;
	struct zebu_equality_expression* left;
	struct zebu_token* n;
	struct zebu_relational_expression* right;
	unsigned refcount, startline, endline;
};

struct zebu_exclusive_or_expression
{
	struct zebu_and_expression* base;
	struct zebu_exclusive_or_expression* left;
	struct zebu_and_expression* right;
	unsigned refcount, startline, endline;
};

struct zebu_exponentiation_expression
{
	struct zebu_unary_expression* base;
	struct zebu_exponentiation_expression* left;
	struct zebu_unary_expression* right;
	unsigned refcount, startline, endline;
};

struct zebu_expression
{
	struct zebu_let_expression* base;
	unsigned refcount, startline, endline;
};

struct zebu_grammar
{
	struct zebu_grammar_juxtaposition* base;
	struct {
		struct zebu_grammar_juxtaposition** data;
		unsigned n, cap;
	} ors;
	unsigned refcount, startline, endline;
};

struct zebu_grammar_highest
{
	struct zebu_token* character;
	struct zebu_charset* charset;
	struct zebu_token* integer;
	struct zebu_token* name;
	struct zebu_regex* regex;
	struct zebu_token* string;
	struct zebu_grammar* subgrammar;
	struct {
		struct zebu_token** data;
		unsigned n, cap;
	} tags;
	struct zebu_tokentype* tokentype;
	unsigned refcount, startline, endline;
};

struct zebu_grammar_juxtaposition
{
	struct zebu_grammar_postfix* base;
	struct {
		struct zebu_grammar_postfix** data;
		unsigned n, cap;
	} juxtapositions;
	unsigned refcount, startline, endline;
};

struct zebu_grammar_postfix
{
	struct zebu_grammar_highest* base;
	struct zebu_token* c;
	struct zebu_token* m;
	struct zebu_token* n;
	struct zebu_token* plus;
	struct zebu_token* qmark;
	struct zebu_token* star;
	unsigned refcount, startline, endline;
};

struct zebu_grammar_rule
{
	struct zebu_grammar* grammar;
	struct zebu_token* name;
	unsigned refcount, startline, endline;
};

struct zebu_implication_expression
{
	struct zebu_possession_expression* base;
	struct zebu_implication_expression* implies;
	unsigned refcount, startline, endline;
};

struct zebu_include_directive
{
	struct zebu_token* path;
	unsigned refcount, startline, endline;
};

struct zebu_inclusion_expression
{
	struct zebu_logical_or_expression* base;
	struct zebu_logical_or_expression* container;
	unsigned refcount, startline, endline;
};

struct zebu_inclusive_or_expression
{
	struct zebu_exclusive_or_expression* base;
	struct zebu_inclusive_or_expression* left;
	struct zebu_exclusive_or_expression* right;
	unsigned refcount, startline, endline;
};

struct zebu_lambda_expression
{
	struct zebu_conditional_expression* base;
	struct zebu_let_expression* lambda;
	struct zebu_token* name;
	struct {
		struct zebu_1$parameter** data;
		unsigned n, cap;
	} parameters;
	struct zebu_type* rettype;
	struct zebu_primitive_type* type;
	unsigned refcount, startline, endline;
};

struct zebu_let_expression
{
	struct zebu_lambda_expression* base;
	struct zebu_let_expression* body;
	struct zebu_token* let;
	struct {
		struct zebu_2$parameter** data;
		unsigned n, cap;
	} parameters;
	unsigned refcount, startline, endline;
};

struct zebu_logical_and_expression
{
	struct zebu_inclusive_or_expression* base;
	struct zebu_logical_and_expression* left;
	struct zebu_inclusive_or_expression* right;
	unsigned refcount, startline, endline;
};

struct zebu_logical_or_expression
{
	struct zebu_logical_and_expression* base;
	struct zebu_logical_or_expression* left;
	struct zebu_logical_and_expression* right;
	unsigned refcount, startline, endline;
};

struct zebu_match_expression
{
	struct zebu_equality_expression* base;
	struct zebu_regex* pattern;
	unsigned refcount, startline, endline;
};

struct zebu_multiplicative_expression
{
	struct zebu_exponentiation_expression* base;
	struct zebu_multiplicative_expression* left;
	struct zebu_token* mult;
	struct zebu_token* qdiv;
	struct zebu_token* rdiv;
	struct zebu_exponentiation_expression* right;
	unsigned refcount, startline, endline;
};

struct zebu_parse_statement
{
	struct zebu_token* argv;
	struct zebu_expression* expression;
	struct zebu_grammar* grammar;
	struct zebu_token* parse;
	unsigned refcount, startline, endline;
};

struct zebu_possession_expression
{
	struct zebu_inclusion_expression* base;
	struct zebu_token* has;
	unsigned refcount, startline, endline;
};

struct zebu_postfix_expression
{
	struct {
		struct zebu_expression** data;
		unsigned n, cap;
	} args;
	struct zebu_primary_expression* base;
	struct zebu_token* call;
	struct zebu_expression* endindex;
	struct zebu_token* field;
	struct zebu_expression* index;
	struct zebu_token* slice;
	struct zebu_expression* startindex;
	struct zebu_postfix_expression* sub;
	struct zebu_token* tupleindex;
	unsigned refcount, startline, endline;
};

struct zebu_primary_expression
{
	struct zebu_token* all_form;
	struct zebu_token* any_form;
	struct zebu_expression* arg;
	struct {
		struct zebu_expression** data;
		unsigned n, cap;
	} args;
	struct zebu_token* bool_form;
	struct zebu_token* comma;
	struct zebu_token* crossmap_form;
	struct zebu_token* curly;
	struct {
		struct zebu_expression** data;
		unsigned n, cap;
	} elements;
	struct zebu_type* emptykey;
	struct zebu_type* emptyset;
	struct zebu_type* emptytype;
	struct zebu_type* emptyvalue;
	struct zebu_token* false_literal;
	struct zebu_token* filter_form;
	struct zebu_token* float_form;
	struct zebu_token* float_literal;
	struct zebu_token* identifier;
	struct zebu_token* int_form;
	struct zebu_token* integer_literal;
	struct zebu_token* isabspath_form;
	struct zebu_token* isaccessibleto_form;
	struct zebu_token* isdir_form;
	struct zebu_token* isexecutableby_form;
	struct {
		struct zebu_0$keyvalue** data;
		unsigned n, cap;
	} keyvalues;
	struct zebu_token* len_form;
	struct zebu_token* list;
	struct zebu_token* map_form;
	struct zebu_token* paren;
	struct zebu_token* range_form;
	struct zebu_token* reduce_form;
	struct zebu_token* string_literal;
	struct zebu_token* sum_form;
	struct zebu_token* true_literal;
	unsigned refcount, startline, endline;
};

struct zebu_primitive_type
{
	struct zebu_token* array;
	struct zebu_token* bool_type;
	struct zebu_token* comma;
	struct {
		struct zebu_type** data;
		unsigned n, cap;
	} elements;
	struct zebu_primitive_type* eletype;
	struct zebu_token* float_type;
	struct zebu_token* grammar;
	struct zebu_token* int_type;
	struct zebu_token* paren;
	struct zebu_token* set;
	struct zebu_token* string_type;
	unsigned refcount, startline, endline;
};

struct zebu_print_statement
{
	struct zebu_expression* expression;
	struct zebu_token* print;
	unsigned refcount, startline, endline;
};

struct zebu_regex
{
	struct zebu_regex_juxtaposition* base;
	struct {
		struct zebu_regex_juxtaposition** data;
		unsigned n, cap;
	} ors;
	unsigned refcount, startline, endline;
};

struct zebu_regex_highest
{
	struct zebu_token* character;
	struct zebu_charset* charset;
	struct zebu_token* integer;
	struct zebu_token* string;
	struct zebu_regex* subregex;
	unsigned refcount, startline, endline;
};

struct zebu_regex_juxtaposition
{
	struct zebu_regex_postfix* base;
	struct {
		struct zebu_regex_postfix** data;
		unsigned n, cap;
	} juxtapositions;
	unsigned refcount, startline, endline;
};

struct zebu_regex_postfix
{
	struct zebu_regex_highest* base;
	struct zebu_token* c;
	struct zebu_token* m;
	struct zebu_token* n;
	struct zebu_token* plus;
	struct zebu_token* qmark;
	struct zebu_token* star;
	unsigned refcount, startline, endline;
};

struct zebu_relational_expression
{
	struct zebu_shift_expression* base;
	struct zebu_token* gt;
	struct zebu_token* gte;
	struct zebu_relational_expression* left;
	struct zebu_token* lt;
	struct zebu_token* lte;
	struct zebu_shift_expression* right;
	unsigned refcount, startline, endline;
};

struct zebu_shift_expression
{
	struct zebu_additive_expression* base;
	struct zebu_shift_expression* left;
	struct zebu_token* lshift;
	struct zebu_additive_expression* right;
	struct zebu_token* rshift;
	unsigned refcount, startline, endline;
};

struct zebu_skip_directive
{
	struct zebu_regex* regex;
	unsigned refcount, startline, endline;
};

struct zebu_statement
{
	struct zebu_assert_statement* assert;
	struct zebu_declare_statement* declare;
	struct zebu_grammar_rule* grammar;
	struct zebu_include_directive* include;
	struct zebu_parse_statement* parse;
	struct zebu_print_statement* print;
	struct zebu_skip_directive* skip;
	unsigned refcount, startline, endline;
};

struct zebu_tokentype
{
	struct zebu_token* bool_;
	struct zebu_token* float_;
	struct zebu_token* int_;
	unsigned refcount, startline, endline;
};

struct zebu_type
{
	struct {
		struct zebu_primitive_type** data;
		unsigned n, cap;
	} args;
	struct zebu_primitive_type* base;
	struct zebu_primitive_type* keytype;
	struct zebu_token* lambda;
	struct zebu_type* rettype;
	struct zebu_type* valuetype;
	unsigned refcount, startline, endline;
};

struct zebu_unary_expression
{
	struct zebu_postfix_expression* base;
	struct zebu_token* bitnot;
	struct zebu_token* lognot;
	struct zebu_token* minus;
	struct zebu_token* plus;
	struct zebu_unary_expression* sub;
	unsigned refcount, startline, endline;
};



extern struct zebu_token* inc_zebu_token(struct zebu_token* token);
extern struct zebu_$start* inc_zebu_$start(struct zebu_$start* ptree);
extern struct zebu_0$keyvalue* inc_zebu_0$keyvalue(struct zebu_0$keyvalue* ptree);
extern struct zebu_1$parameter* inc_zebu_1$parameter(struct zebu_1$parameter* ptree);
extern struct zebu_2$parameter* inc_zebu_2$parameter(struct zebu_2$parameter* ptree);
extern struct zebu_additive_expression* inc_zebu_additive_expression(struct zebu_additive_expression* ptree);
extern struct zebu_and_expression* inc_zebu_and_expression(struct zebu_and_expression* ptree);
extern struct zebu_assert_statement* inc_zebu_assert_statement(struct zebu_assert_statement* ptree);
extern struct zebu_charset* inc_zebu_charset(struct zebu_charset* ptree);
extern struct zebu_charset_highest* inc_zebu_charset_highest(struct zebu_charset_highest* ptree);
extern struct zebu_charset_intersect* inc_zebu_charset_intersect(struct zebu_charset_intersect* ptree);
extern struct zebu_charset_prefix* inc_zebu_charset_prefix(struct zebu_charset_prefix* ptree);
extern struct zebu_charset_range* inc_zebu_charset_range(struct zebu_charset_range* ptree);
extern struct zebu_charset_symdiff* inc_zebu_charset_symdiff(struct zebu_charset_symdiff* ptree);
extern struct zebu_conditional_expression* inc_zebu_conditional_expression(struct zebu_conditional_expression* ptree);
extern struct zebu_declare_statement* inc_zebu_declare_statement(struct zebu_declare_statement* ptree);
extern struct zebu_equality_expression* inc_zebu_equality_expression(struct zebu_equality_expression* ptree);
extern struct zebu_exclusive_or_expression* inc_zebu_exclusive_or_expression(struct zebu_exclusive_or_expression* ptree);
extern struct zebu_exponentiation_expression* inc_zebu_exponentiation_expression(struct zebu_exponentiation_expression* ptree);
extern struct zebu_expression* inc_zebu_expression(struct zebu_expression* ptree);
extern struct zebu_grammar* inc_zebu_grammar(struct zebu_grammar* ptree);
extern struct zebu_grammar_highest* inc_zebu_grammar_highest(struct zebu_grammar_highest* ptree);
extern struct zebu_grammar_juxtaposition* inc_zebu_grammar_juxtaposition(struct zebu_grammar_juxtaposition* ptree);
extern struct zebu_grammar_postfix* inc_zebu_grammar_postfix(struct zebu_grammar_postfix* ptree);
extern struct zebu_grammar_rule* inc_zebu_grammar_rule(struct zebu_grammar_rule* ptree);
extern struct zebu_implication_expression* inc_zebu_implication_expression(struct zebu_implication_expression* ptree);
extern struct zebu_include_directive* inc_zebu_include_directive(struct zebu_include_directive* ptree);
extern struct zebu_inclusion_expression* inc_zebu_inclusion_expression(struct zebu_inclusion_expression* ptree);
extern struct zebu_inclusive_or_expression* inc_zebu_inclusive_or_expression(struct zebu_inclusive_or_expression* ptree);
extern struct zebu_lambda_expression* inc_zebu_lambda_expression(struct zebu_lambda_expression* ptree);
extern struct zebu_let_expression* inc_zebu_let_expression(struct zebu_let_expression* ptree);
extern struct zebu_logical_and_expression* inc_zebu_logical_and_expression(struct zebu_logical_and_expression* ptree);
extern struct zebu_logical_or_expression* inc_zebu_logical_or_expression(struct zebu_logical_or_expression* ptree);
extern struct zebu_match_expression* inc_zebu_match_expression(struct zebu_match_expression* ptree);
extern struct zebu_multiplicative_expression* inc_zebu_multiplicative_expression(struct zebu_multiplicative_expression* ptree);
extern struct zebu_parse_statement* inc_zebu_parse_statement(struct zebu_parse_statement* ptree);
extern struct zebu_possession_expression* inc_zebu_possession_expression(struct zebu_possession_expression* ptree);
extern struct zebu_postfix_expression* inc_zebu_postfix_expression(struct zebu_postfix_expression* ptree);
extern struct zebu_primary_expression* inc_zebu_primary_expression(struct zebu_primary_expression* ptree);
extern struct zebu_primitive_type* inc_zebu_primitive_type(struct zebu_primitive_type* ptree);
extern struct zebu_print_statement* inc_zebu_print_statement(struct zebu_print_statement* ptree);
extern struct zebu_regex* inc_zebu_regex(struct zebu_regex* ptree);
extern struct zebu_regex_highest* inc_zebu_regex_highest(struct zebu_regex_highest* ptree);
extern struct zebu_regex_juxtaposition* inc_zebu_regex_juxtaposition(struct zebu_regex_juxtaposition* ptree);
extern struct zebu_regex_postfix* inc_zebu_regex_postfix(struct zebu_regex_postfix* ptree);
extern struct zebu_relational_expression* inc_zebu_relational_expression(struct zebu_relational_expression* ptree);
extern struct zebu_shift_expression* inc_zebu_shift_expression(struct zebu_shift_expression* ptree);
extern struct zebu_skip_directive* inc_zebu_skip_directive(struct zebu_skip_directive* ptree);
extern struct zebu_statement* inc_zebu_statement(struct zebu_statement* ptree);
extern struct zebu_tokentype* inc_zebu_tokentype(struct zebu_tokentype* ptree);
extern struct zebu_type* inc_zebu_type(struct zebu_type* ptree);
extern struct zebu_unary_expression* inc_zebu_unary_expression(struct zebu_unary_expression* ptree);


extern void free_zebu_token(struct zebu_token* token);
extern void free_zebu_$start(struct zebu_$start* ptree);

extern void free_zebu_0$keyvalue(struct zebu_0$keyvalue* ptree);

extern void free_zebu_1$parameter(struct zebu_1$parameter* ptree);

extern void free_zebu_2$parameter(struct zebu_2$parameter* ptree);

extern void free_zebu_additive_expression(struct zebu_additive_expression* ptree);

extern void free_zebu_and_expression(struct zebu_and_expression* ptree);

extern void free_zebu_assert_statement(struct zebu_assert_statement* ptree);

extern void free_zebu_charset(struct zebu_charset* ptree);

extern void free_zebu_charset_highest(struct zebu_charset_highest* ptree);

extern void free_zebu_charset_intersect(struct zebu_charset_intersect* ptree);

extern void free_zebu_charset_prefix(struct zebu_charset_prefix* ptree);

extern void free_zebu_charset_range(struct zebu_charset_range* ptree);

extern void free_zebu_charset_symdiff(struct zebu_charset_symdiff* ptree);

extern void free_zebu_conditional_expression(struct zebu_conditional_expression* ptree);

extern void free_zebu_declare_statement(struct zebu_declare_statement* ptree);

extern void free_zebu_equality_expression(struct zebu_equality_expression* ptree);

extern void free_zebu_exclusive_or_expression(struct zebu_exclusive_or_expression* ptree);

extern void free_zebu_exponentiation_expression(struct zebu_exponentiation_expression* ptree);

extern void free_zebu_expression(struct zebu_expression* ptree);

extern void free_zebu_grammar(struct zebu_grammar* ptree);

extern void free_zebu_grammar_highest(struct zebu_grammar_highest* ptree);

extern void free_zebu_grammar_juxtaposition(struct zebu_grammar_juxtaposition* ptree);

extern void free_zebu_grammar_postfix(struct zebu_grammar_postfix* ptree);

extern void free_zebu_grammar_rule(struct zebu_grammar_rule* ptree);

extern void free_zebu_implication_expression(struct zebu_implication_expression* ptree);

extern void free_zebu_include_directive(struct zebu_include_directive* ptree);

extern void free_zebu_inclusion_expression(struct zebu_inclusion_expression* ptree);

extern void free_zebu_inclusive_or_expression(struct zebu_inclusive_or_expression* ptree);

extern void free_zebu_lambda_expression(struct zebu_lambda_expression* ptree);

extern void free_zebu_let_expression(struct zebu_let_expression* ptree);

extern void free_zebu_logical_and_expression(struct zebu_logical_and_expression* ptree);

extern void free_zebu_logical_or_expression(struct zebu_logical_or_expression* ptree);

extern void free_zebu_match_expression(struct zebu_match_expression* ptree);

extern void free_zebu_multiplicative_expression(struct zebu_multiplicative_expression* ptree);

extern void free_zebu_parse_statement(struct zebu_parse_statement* ptree);

extern void free_zebu_possession_expression(struct zebu_possession_expression* ptree);

extern void free_zebu_postfix_expression(struct zebu_postfix_expression* ptree);

extern void free_zebu_primary_expression(struct zebu_primary_expression* ptree);

extern void free_zebu_primitive_type(struct zebu_primitive_type* ptree);

extern void free_zebu_print_statement(struct zebu_print_statement* ptree);

extern void free_zebu_regex(struct zebu_regex* ptree);

extern void free_zebu_regex_highest(struct zebu_regex_highest* ptree);

extern void free_zebu_regex_juxtaposition(struct zebu_regex_juxtaposition* ptree);

extern void free_zebu_regex_postfix(struct zebu_regex_postfix* ptree);

extern void free_zebu_relational_expression(struct zebu_relational_expression* ptree);

extern void free_zebu_shift_expression(struct zebu_shift_expression* ptree);

extern void free_zebu_skip_directive(struct zebu_skip_directive* ptree);

extern void free_zebu_statement(struct zebu_statement* ptree);

extern void free_zebu_tokentype(struct zebu_tokentype* ptree);

extern void free_zebu_type(struct zebu_type* ptree);

extern void free_zebu_unary_expression(struct zebu_unary_expression* ptree);



struct zebu_$start* zebu_parse(FILE* stream);
