
#ifndef ENUM_EXPRESSION_KIND
#define ENUM_EXPRESSION_KIND

enum expression_kind
{
	ek_parenthesis,
	
	ek_variable,
	ek_set,
	ek_list,
	ek_dict,
	ek_tuple,
	ek_literal,
	
	ek_all_form,
	ek_set_form,
	ek_len_form,
	ek_int_form,
	ek_any_form,
	ek_map_form,
	ek_sum_form,
	ek_list_form,
	ek_dict_form,
	ek_tuple_form,
	ek_float_form,
	ek_range_form,
	ek_isdir_form,
	ek_crossmap_form,
	ek_isabspath_form,
	ek_isaccessibleto_form,
	ek_isexecutableby_form,
	
	ek_funccall,
	ek_dict_index,
	ek_list_index,
	ek_list_sublist,
	ek_tuple_index,
	ek_fieldaccess,
	
	ek_bool_not,
	
	ek_int_math,
	ek_set_math,
	ek_dict_math,
	ek_float_math,
	ek_list_concat,
	ek_tuple_concat,
	
	ek_comparison,
	
	ek_regex_match,
	
	ek_logical_or,
	
	ek_logical_and,
	
	ek_ternary,
	
	ek_set_contains,
	ek_list_contains,
	ek_dict_contains,
	
	ek_has,
	
	ek_implication,
	
	ek_lambda,
	
	ek_let,
};

#endif











