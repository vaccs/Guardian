
#include <stdio.h>

struct token
{
	unsigned char* data;
	unsigned len, refcount;
};

struct zebu_$start
{
	struct zebu_root* root;
	unsigned refcount;
};

struct zebu_additive_expression
{
	unsigned refcount;
};

struct zebu_and_expression
{
	unsigned refcount;
};

struct zebu_charset
{
	unsigned refcount;
};

struct zebu_charset_highest
{
	unsigned refcount;
};

struct zebu_charset_intersect
{
	unsigned refcount;
};

struct zebu_charset_prefix
{
	unsigned refcount;
};

struct zebu_charset_range
{
	unsigned refcount;
};

struct zebu_charset_symdif
{
	unsigned refcount;
};

struct zebu_conditional_expression
{
	unsigned refcount;
};

struct zebu_entry
{
	struct zebu_expression* assertion;
	struct token* debug;
	struct token* error;
	struct zebu_expression* expression;
	struct zebu_grammar* grammar;
	struct token* note;
	struct token* path;
	struct zebu_regex* regex;
	struct token* skip;
	struct token* start;
	struct token* using;
	struct token* warning;
	unsigned refcount;
};

struct zebu_equality_expression
{
	unsigned refcount;
};

struct zebu_exclusive_or_expression
{
	unsigned refcount;
};

struct zebu_exponentiation_expression
{
	unsigned refcount;
};

struct zebu_expression
{
	unsigned refcount;
};

struct zebu_grammar
{
	unsigned refcount;
};

struct zebu_grammar_highest
{
	unsigned refcount;
};

struct zebu_grammar_jux
{
	unsigned refcount;
};

struct zebu_grammar_postfix
{
	unsigned refcount;
};

struct zebu_implication_expression
{
	unsigned refcount;
};

struct zebu_inclusive_or_expression
{
	unsigned refcount;
};

struct zebu_lambda_expression
{
	unsigned refcount;
};

struct zebu_logical_and_expression
{
	unsigned refcount;
};

struct zebu_logical_or_expression
{
	unsigned refcount;
};

struct zebu_multiplicative_expression
{
	unsigned refcount;
};

struct zebu_possession_expression
{
	unsigned refcount;
};

struct zebu_postfix_expression
{
	unsigned refcount;
};

struct zebu_primary_expression
{
	unsigned refcount;
};

struct zebu_primary_type
{
	unsigned refcount;
};

struct zebu_regex
{
	unsigned refcount;
};

struct zebu_regex_highest
{
	unsigned refcount;
};

struct zebu_regex_jux
{
	unsigned refcount;
};

struct zebu_regex_postfix
{
	unsigned refcount;
};

struct zebu_relational_expression
{
	unsigned refcount;
};

struct zebu_root
{
	struct {
		struct zebu_entry** data;
		unsigned n, cap;
	} entries;
	unsigned refcount;
};

struct zebu_shift_expression
{
	unsigned refcount;
};

struct zebu_type
{
	unsigned refcount;
};

struct zebu_unary_expression
{
	unsigned refcount;
};



extern struct token* inc_token(struct token* this);
extern struct zebu_$start* inc_zebu_$start_ptree(struct zebu_$start* ptree);
extern struct zebu_additive_expression* inc_zebu_additive_expression_ptree(struct zebu_additive_expression* ptree);
extern struct zebu_and_expression* inc_zebu_and_expression_ptree(struct zebu_and_expression* ptree);
extern struct zebu_charset* inc_zebu_charset_ptree(struct zebu_charset* ptree);
extern struct zebu_charset_highest* inc_zebu_charset_highest_ptree(struct zebu_charset_highest* ptree);
extern struct zebu_charset_intersect* inc_zebu_charset_intersect_ptree(struct zebu_charset_intersect* ptree);
extern struct zebu_charset_prefix* inc_zebu_charset_prefix_ptree(struct zebu_charset_prefix* ptree);
extern struct zebu_charset_range* inc_zebu_charset_range_ptree(struct zebu_charset_range* ptree);
extern struct zebu_charset_symdif* inc_zebu_charset_symdif_ptree(struct zebu_charset_symdif* ptree);
extern struct zebu_conditional_expression* inc_zebu_conditional_expression_ptree(struct zebu_conditional_expression* ptree);
extern struct zebu_entry* inc_zebu_entry_ptree(struct zebu_entry* ptree);
extern struct zebu_equality_expression* inc_zebu_equality_expression_ptree(struct zebu_equality_expression* ptree);
extern struct zebu_exclusive_or_expression* inc_zebu_exclusive_or_expression_ptree(struct zebu_exclusive_or_expression* ptree);
extern struct zebu_exponentiation_expression* inc_zebu_exponentiation_expression_ptree(struct zebu_exponentiation_expression* ptree);
extern struct zebu_expression* inc_zebu_expression_ptree(struct zebu_expression* ptree);
extern struct zebu_grammar* inc_zebu_grammar_ptree(struct zebu_grammar* ptree);
extern struct zebu_grammar_highest* inc_zebu_grammar_highest_ptree(struct zebu_grammar_highest* ptree);
extern struct zebu_grammar_jux* inc_zebu_grammar_jux_ptree(struct zebu_grammar_jux* ptree);
extern struct zebu_grammar_postfix* inc_zebu_grammar_postfix_ptree(struct zebu_grammar_postfix* ptree);
extern struct zebu_implication_expression* inc_zebu_implication_expression_ptree(struct zebu_implication_expression* ptree);
extern struct zebu_inclusive_or_expression* inc_zebu_inclusive_or_expression_ptree(struct zebu_inclusive_or_expression* ptree);
extern struct zebu_lambda_expression* inc_zebu_lambda_expression_ptree(struct zebu_lambda_expression* ptree);
extern struct zebu_logical_and_expression* inc_zebu_logical_and_expression_ptree(struct zebu_logical_and_expression* ptree);
extern struct zebu_logical_or_expression* inc_zebu_logical_or_expression_ptree(struct zebu_logical_or_expression* ptree);
extern struct zebu_multiplicative_expression* inc_zebu_multiplicative_expression_ptree(struct zebu_multiplicative_expression* ptree);
extern struct zebu_possession_expression* inc_zebu_possession_expression_ptree(struct zebu_possession_expression* ptree);
extern struct zebu_postfix_expression* inc_zebu_postfix_expression_ptree(struct zebu_postfix_expression* ptree);
extern struct zebu_primary_expression* inc_zebu_primary_expression_ptree(struct zebu_primary_expression* ptree);
extern struct zebu_primary_type* inc_zebu_primary_type_ptree(struct zebu_primary_type* ptree);
extern struct zebu_regex* inc_zebu_regex_ptree(struct zebu_regex* ptree);
extern struct zebu_regex_highest* inc_zebu_regex_highest_ptree(struct zebu_regex_highest* ptree);
extern struct zebu_regex_jux* inc_zebu_regex_jux_ptree(struct zebu_regex_jux* ptree);
extern struct zebu_regex_postfix* inc_zebu_regex_postfix_ptree(struct zebu_regex_postfix* ptree);
extern struct zebu_relational_expression* inc_zebu_relational_expression_ptree(struct zebu_relational_expression* ptree);
extern struct zebu_root* inc_zebu_root_ptree(struct zebu_root* ptree);
extern struct zebu_shift_expression* inc_zebu_shift_expression_ptree(struct zebu_shift_expression* ptree);
extern struct zebu_type* inc_zebu_type_ptree(struct zebu_type* ptree);
extern struct zebu_unary_expression* inc_zebu_unary_expression_ptree(struct zebu_unary_expression* ptree);


extern void free_token(struct token* this);
extern void free_zebu_$start_ptree(struct zebu_$start* ptree);

extern void free_zebu_additive_expression_ptree(struct zebu_additive_expression* ptree);

extern void free_zebu_and_expression_ptree(struct zebu_and_expression* ptree);

extern void free_zebu_charset_ptree(struct zebu_charset* ptree);

extern void free_zebu_charset_highest_ptree(struct zebu_charset_highest* ptree);

extern void free_zebu_charset_intersect_ptree(struct zebu_charset_intersect* ptree);

extern void free_zebu_charset_prefix_ptree(struct zebu_charset_prefix* ptree);

extern void free_zebu_charset_range_ptree(struct zebu_charset_range* ptree);

extern void free_zebu_charset_symdif_ptree(struct zebu_charset_symdif* ptree);

extern void free_zebu_conditional_expression_ptree(struct zebu_conditional_expression* ptree);

extern void free_zebu_entry_ptree(struct zebu_entry* ptree);

extern void free_zebu_equality_expression_ptree(struct zebu_equality_expression* ptree);

extern void free_zebu_exclusive_or_expression_ptree(struct zebu_exclusive_or_expression* ptree);

extern void free_zebu_exponentiation_expression_ptree(struct zebu_exponentiation_expression* ptree);

extern void free_zebu_expression_ptree(struct zebu_expression* ptree);

extern void free_zebu_grammar_ptree(struct zebu_grammar* ptree);

extern void free_zebu_grammar_highest_ptree(struct zebu_grammar_highest* ptree);

extern void free_zebu_grammar_jux_ptree(struct zebu_grammar_jux* ptree);

extern void free_zebu_grammar_postfix_ptree(struct zebu_grammar_postfix* ptree);

extern void free_zebu_implication_expression_ptree(struct zebu_implication_expression* ptree);

extern void free_zebu_inclusive_or_expression_ptree(struct zebu_inclusive_or_expression* ptree);

extern void free_zebu_lambda_expression_ptree(struct zebu_lambda_expression* ptree);

extern void free_zebu_logical_and_expression_ptree(struct zebu_logical_and_expression* ptree);

extern void free_zebu_logical_or_expression_ptree(struct zebu_logical_or_expression* ptree);

extern void free_zebu_multiplicative_expression_ptree(struct zebu_multiplicative_expression* ptree);

extern void free_zebu_possession_expression_ptree(struct zebu_possession_expression* ptree);

extern void free_zebu_postfix_expression_ptree(struct zebu_postfix_expression* ptree);

extern void free_zebu_primary_expression_ptree(struct zebu_primary_expression* ptree);

extern void free_zebu_primary_type_ptree(struct zebu_primary_type* ptree);

extern void free_zebu_regex_ptree(struct zebu_regex* ptree);

extern void free_zebu_regex_highest_ptree(struct zebu_regex_highest* ptree);

extern void free_zebu_regex_jux_ptree(struct zebu_regex_jux* ptree);

extern void free_zebu_regex_postfix_ptree(struct zebu_regex_postfix* ptree);

extern void free_zebu_relational_expression_ptree(struct zebu_relational_expression* ptree);

extern void free_zebu_root_ptree(struct zebu_root* ptree);

extern void free_zebu_shift_expression_ptree(struct zebu_shift_expression* ptree);

extern void free_zebu_type_ptree(struct zebu_type* ptree);

extern void free_zebu_unary_expression_ptree(struct zebu_unary_expression* ptree);



struct zebu_$start* zebu_parse(FILE* stream);
