
enum token
{
	// tokens:
	t_EOF,
	
	t_colon,
	t_slash,
	t_semicolon,
	t_osquare, t_csquare,
	t_oparen, t_cparen,
	t_plus,
	t_asterisk,
	t_qmark,
	t_ocurly,
	t_vbar,
	t_equals,
	t_emark,
	t_comma,
	t_ampersand,
	t_caret,
	t_dash,
	
	t_scalar_hashtag,
	t_array_hashtag,
	
	t_octal_literal,
	t_decimal_literal,
	t_hexadecimal_literal,
	
	t_identifier,
	
	t_directive,
	
	t_character,
	t_string,
	
	t_enforcement_level,
	
	number_of_tokens,
};

