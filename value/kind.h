
#ifndef ENUM_VALUE_KIND
#define ENUM_VALUE_KIND

enum value_kind
{
	vk_int,
	vk_bool,
	vk_float,
	vk_string,
	
	vk_set,
	vk_list,
	vk_dict,
	vk_tuple,
	vk_lambda,
	
	vk_environment,
};

#endif
