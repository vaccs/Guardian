
#include <stdio.h>

struct zebu_token
{
	unsigned char* data;
	unsigned len, refcount;
};

struct zebu_$start
{
	struct {
		struct zebu_assertion** data;
		unsigned n, cap;
	} assertions;
	struct {
		struct zebu_value_declare** data;
		unsigned n, cap;
	} declares;
	struct {
		struct zebu_grammar_rule** data;
		unsigned n, cap;
	} grammars;
	struct {
		struct zebu_skip_directive** data;
		unsigned n, cap;
	} skips;
	struct {
		struct zebu_start_directive** data;
		unsigned n, cap;
	} starts;
	struct {
		struct zebu_using_directive** data;
		unsigned n, cap;
	} usings;
	unsigned refcount;
};

struct zebu_0$parameter
{
	struct zebu_token* name;
	struct zebu_type* type;
	unsigned refcount;
};

struct zebu_additive_expression
{
	struct zebu_multiplicative_expression* base;
	struct zebu_additive_expression* left;
	struct zebu_multiplicative_expression* right;
	unsigned refcount;
};

struct zebu_and_expression
{
	struct zebu_equality_expression* base;
	struct zebu_and_expression* left;
	struct zebu_equality_expression* right;
	unsigned refcount;
};

struct zebu_assertion
{
	struct zebu_token* debug;
	struct zebu_token* error;
	struct zebu_expression* expression;
	struct zebu_token* note;
	struct zebu_token* warning;
	unsigned refcount;
};

struct zebu_charset
{
	struct zebu_charset_symdiff* base;
	struct {
		struct zebu_charset_symdiff** data;
		unsigned n, cap;
	} ors;
	unsigned refcount;
};

struct zebu_charset_highest
{
	struct zebu_token* character;
	struct zebu_token* integer;
	struct zebu_charset* subcharset;
	unsigned refcount;
};

struct zebu_charset_intersect
{
	struct zebu_charset_range* base;
	struct {
		struct zebu_charset_range** data;
		unsigned n, cap;
	} intersects;
	unsigned refcount;
};

struct zebu_charset_prefix
{
	struct zebu_charset_highest* base;
	struct zebu_token* emark;
	unsigned refcount;
};

struct zebu_charset_range
{
	struct zebu_charset_prefix* left;
	struct zebu_charset_prefix* right;
	unsigned refcount;
};

struct zebu_charset_symdiff
{
	struct zebu_charset_intersect* base;
	struct {
		struct zebu_charset_intersect** data;
		unsigned n, cap;
	} xors;
	unsigned refcount;
};

struct zebu_conditional_expression
{
	struct zebu_logical_or_expression* base;
	struct zebu_conditional_expression* false_case;
	struct zebu_expression* true_case;
	unsigned refcount;
};

struct zebu_equality_expression
{
	struct zebu_relational_expression* base;
	struct zebu_equality_expression* left;
	struct zebu_relational_expression* right;
	unsigned refcount;
};

struct zebu_exclusive_or_expression
{
	struct zebu_and_expression* base;
	struct zebu_exclusive_or_expression* left;
	struct zebu_and_expression* right;
	unsigned refcount;
};

struct zebu_exponentiation_expression
{
	struct zebu_unary_expression* base;
	struct zebu_exponentiation_expression* left;
	struct zebu_unary_expression* right;
	unsigned refcount;
};

struct zebu_expression
{
	struct zebu_implication_expression* base;
	struct {
		struct zebu_implication_expression** data;
		unsigned n, cap;
	} iffs;
	unsigned refcount;
};

struct zebu_grammar
{
	struct zebu_grammar_juxtaposition* base;
	struct {
		struct zebu_grammar_juxtaposition** data;
		unsigned n, cap;
	} ors;
	unsigned refcount;
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
	unsigned refcount;
};

struct zebu_grammar_juxtaposition
{
	struct zebu_grammar_postfix* base;
	struct {
		struct zebu_grammar_postfix** data;
		unsigned n, cap;
	} juxtapositions;
	unsigned refcount;
};

struct zebu_grammar_postfix
{
	struct zebu_grammar_highest* base;
	struct zebu_token* plus;
	struct zebu_token* qmark;
	struct zebu_token* star;
	unsigned refcount;
};

struct zebu_grammar_rule
{
	struct zebu_grammar* grammar;
	struct zebu_token* name;
	unsigned refcount;
};

struct zebu_implication_expression
{
	struct zebu_possession_expression* base;
	struct {
		struct zebu_possession_expression** data;
		unsigned n, cap;
	} implies;
	unsigned refcount;
};

struct zebu_inclusive_or_expression
{
	struct zebu_exclusive_or_expression* base;
	struct zebu_inclusive_or_expression* left;
	struct zebu_exclusive_or_expression* right;
	unsigned refcount;
};

struct zebu_lambda_expression
{
	struct zebu_conditional_expression* base;
	struct zebu_lambda_expression* lambda;
	struct unresolved* lambda_captures;
	struct zebu_token* name;
	struct {
		struct zebu_0$parameter** data;
		unsigned n, cap;
	} parameters;
	struct zebu_type* type;
	unsigned refcount;
};

struct zebu_logical_and_expression
{
	struct zebu_inclusive_or_expression* base;
	struct zebu_logical_and_expression* left;
	struct zebu_inclusive_or_expression* right;
	unsigned refcount;
};

struct zebu_logical_or_expression
{
	struct zebu_logical_and_expression* base;
	struct zebu_logical_or_expression* left;
	struct zebu_logical_and_expression* right;
	unsigned refcount;
};

struct zebu_multiplicative_expression
{
	struct zebu_exponentiation_expression* base;
	struct zebu_multiplicative_expression* left;
	struct zebu_exponentiation_expression* right;
	unsigned refcount;
};

struct zebu_possession_expression
{
	struct zebu_lambda_expression* base;
	struct zebu_token* has;
	unsigned refcount;
};

struct zebu_postfix_expression
{
	struct {
		struct zebu_expression** data;
		unsigned n, cap;
	} args;
	struct zebu_primary_expression* base;
	struct zebu_expression* index;
	struct zebu_postfix_expression* sub;
	unsigned refcount;
};

struct zebu_primary_expression
{
	struct zebu_token* character_literal;
	struct {
		struct zebu_expression** data;
		unsigned n, cap;
	} elements;
	struct zebu_token* float_literal;
	struct zebu_token* identifier;
	struct zebu_token* integer_literal;
	struct zebu_token* list;
	struct zebu_token* string_literal;
	struct zebu_token* tuple;
	struct type* type;
	struct value* value;
	unsigned refcount;
};

struct zebu_primary_type
{
	struct zebu_primary_type* array;
	struct zebu_token* bool_type;
	struct zebu_token* char_type;
	struct {
		struct zebu_type** data;
		unsigned n, cap;
	} elements;
	struct zebu_token* float_type;
	struct zebu_token* grammar;
	struct zebu_token* int_type;
	struct zebu_token* tuple;
	unsigned refcount;
};

struct zebu_regex
{
	struct zebu_regex_juxtaposition* base;
	struct {
		struct zebu_regex_juxtaposition** data;
		unsigned n, cap;
	} ors;
	unsigned refcount;
};

struct zebu_regex_highest
{
	struct zebu_token* character;
	struct zebu_charset* charset;
	struct zebu_token* integer;
	struct zebu_token* string;
	struct zebu_regex* subregex;
	unsigned refcount;
};

struct zebu_regex_juxtaposition
{
	struct zebu_regex_postfix* base;
	struct {
		struct zebu_regex_postfix** data;
		unsigned n, cap;
	} juxtapositions;
	unsigned refcount;
};

struct zebu_regex_postfix
{
	struct zebu_regex_highest* base;
	struct zebu_token* plus;
	struct zebu_token* qmark;
	struct zebu_token* star;
	unsigned refcount;
};

struct zebu_relational_expression
{
	struct zebu_shift_expression* base;
	struct zebu_relational_expression* left;
	struct zebu_shift_expression* right;
	unsigned refcount;
};

struct zebu_shift_expression
{
	struct zebu_additive_expression* base;
	struct zebu_shift_expression* left;
	struct zebu_additive_expression* right;
	unsigned refcount;
};

struct zebu_skip_directive
{
	struct zebu_regex* regex;
	unsigned refcount;
};

struct zebu_start_directive
{
	struct zebu_grammar* grammar;
	unsigned refcount;
};

struct zebu_type
{
	struct {
		struct zebu_type** data;
		unsigned n, cap;
	} args;
	struct zebu_primary_type* base;
	struct zebu_type* rettype;
	unsigned refcount;
};

struct zebu_unary_expression
{
	struct zebu_postfix_expression* base;
	struct zebu_unary_expression* sub;
	unsigned refcount;
};

struct zebu_using_directive
{
	struct zebu_token* path;
	unsigned refcount;
};

struct zebu_value_declare
{
	struct zebu_expression* expression;
	struct zebu_token* name;
	unsigned refcount;
};



extern struct zebu_token* inc_zebu_token(struct zebu_token* this);
extern struct zebu_$start* inc_zebu_$start(struct zebu_$start* ptree);
extern struct zebu_0$parameter* inc_zebu_0$parameter(struct zebu_0$parameter* ptree);
extern struct zebu_additive_expression* inc_zebu_additive_expression(struct zebu_additive_expression* ptree);
extern struct zebu_and_expression* inc_zebu_and_expression(struct zebu_and_expression* ptree);
extern struct zebu_assertion* inc_zebu_assertion(struct zebu_assertion* ptree);
extern struct zebu_charset* inc_zebu_charset(struct zebu_charset* ptree);
extern struct zebu_charset_highest* inc_zebu_charset_highest(struct zebu_charset_highest* ptree);
extern struct zebu_charset_intersect* inc_zebu_charset_intersect(struct zebu_charset_intersect* ptree);
extern struct zebu_charset_prefix* inc_zebu_charset_prefix(struct zebu_charset_prefix* ptree);
extern struct zebu_charset_range* inc_zebu_charset_range(struct zebu_charset_range* ptree);
extern struct zebu_charset_symdiff* inc_zebu_charset_symdiff(struct zebu_charset_symdiff* ptree);
extern struct zebu_conditional_expression* inc_zebu_conditional_expression(struct zebu_conditional_expression* ptree);
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
extern struct zebu_inclusive_or_expression* inc_zebu_inclusive_or_expression(struct zebu_inclusive_or_expression* ptree);
extern struct zebu_lambda_expression* inc_zebu_lambda_expression(struct zebu_lambda_expression* ptree);
extern struct zebu_logical_and_expression* inc_zebu_logical_and_expression(struct zebu_logical_and_expression* ptree);
extern struct zebu_logical_or_expression* inc_zebu_logical_or_expression(struct zebu_logical_or_expression* ptree);
extern struct zebu_multiplicative_expression* inc_zebu_multiplicative_expression(struct zebu_multiplicative_expression* ptree);
extern struct zebu_possession_expression* inc_zebu_possession_expression(struct zebu_possession_expression* ptree);
extern struct zebu_postfix_expression* inc_zebu_postfix_expression(struct zebu_postfix_expression* ptree);
extern struct zebu_primary_expression* inc_zebu_primary_expression(struct zebu_primary_expression* ptree);
extern struct zebu_primary_type* inc_zebu_primary_type(struct zebu_primary_type* ptree);
extern struct zebu_regex* inc_zebu_regex(struct zebu_regex* ptree);
extern struct zebu_regex_highest* inc_zebu_regex_highest(struct zebu_regex_highest* ptree);
extern struct zebu_regex_juxtaposition* inc_zebu_regex_juxtaposition(struct zebu_regex_juxtaposition* ptree);
extern struct zebu_regex_postfix* inc_zebu_regex_postfix(struct zebu_regex_postfix* ptree);
extern struct zebu_relational_expression* inc_zebu_relational_expression(struct zebu_relational_expression* ptree);
extern struct zebu_shift_expression* inc_zebu_shift_expression(struct zebu_shift_expression* ptree);
extern struct zebu_skip_directive* inc_zebu_skip_directive(struct zebu_skip_directive* ptree);
extern struct zebu_start_directive* inc_zebu_start_directive(struct zebu_start_directive* ptree);
extern struct zebu_type* inc_zebu_type(struct zebu_type* ptree);
extern struct zebu_unary_expression* inc_zebu_unary_expression(struct zebu_unary_expression* ptree);
extern struct zebu_using_directive* inc_zebu_using_directive(struct zebu_using_directive* ptree);
extern struct zebu_value_declare* inc_zebu_value_declare(struct zebu_value_declare* ptree);


extern void free_zebu_token(struct zebu_token* this);
extern void free_zebu_$start(struct zebu_$start* ptree);

extern void free_zebu_0$parameter(struct zebu_0$parameter* ptree);

extern void free_zebu_additive_expression(struct zebu_additive_expression* ptree);

extern void free_zebu_and_expression(struct zebu_and_expression* ptree);

extern void free_zebu_assertion(struct zebu_assertion* ptree);

extern void free_zebu_charset(struct zebu_charset* ptree);

extern void free_zebu_charset_highest(struct zebu_charset_highest* ptree);

extern void free_zebu_charset_intersect(struct zebu_charset_intersect* ptree);

extern void free_zebu_charset_prefix(struct zebu_charset_prefix* ptree);

extern void free_zebu_charset_range(struct zebu_charset_range* ptree);

extern void free_zebu_charset_symdiff(struct zebu_charset_symdiff* ptree);

extern void free_zebu_conditional_expression(struct zebu_conditional_expression* ptree);

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

extern void free_zebu_inclusive_or_expression(struct zebu_inclusive_or_expression* ptree);

extern void free_zebu_lambda_expression(struct zebu_lambda_expression* ptree);

extern void free_zebu_logical_and_expression(struct zebu_logical_and_expression* ptree);

extern void free_zebu_logical_or_expression(struct zebu_logical_or_expression* ptree);

extern void free_zebu_multiplicative_expression(struct zebu_multiplicative_expression* ptree);

extern void free_zebu_possession_expression(struct zebu_possession_expression* ptree);

extern void free_zebu_postfix_expression(struct zebu_postfix_expression* ptree);

extern void free_zebu_primary_expression(struct zebu_primary_expression* ptree);

extern void free_zebu_primary_type(struct zebu_primary_type* ptree);

extern void free_zebu_regex(struct zebu_regex* ptree);

extern void free_zebu_regex_highest(struct zebu_regex_highest* ptree);

extern void free_zebu_regex_juxtaposition(struct zebu_regex_juxtaposition* ptree);

extern void free_zebu_regex_postfix(struct zebu_regex_postfix* ptree);

extern void free_zebu_relational_expression(struct zebu_relational_expression* ptree);

extern void free_zebu_shift_expression(struct zebu_shift_expression* ptree);

extern void free_zebu_skip_directive(struct zebu_skip_directive* ptree);

extern void free_zebu_start_directive(struct zebu_start_directive* ptree);

extern void free_zebu_type(struct zebu_type* ptree);

extern void free_zebu_unary_expression(struct zebu_unary_expression* ptree);

extern void free_zebu_using_directive(struct zebu_using_directive* ptree);

extern void free_zebu_value_declare(struct zebu_value_declare* ptree);



struct zebu_$start* zebu_parse(FILE* stream);
