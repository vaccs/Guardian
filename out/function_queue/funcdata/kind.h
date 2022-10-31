
#ifndef ENUM_FUNCDATA_KIND
#define ENUM_FUNCDATA_KIND

enum funcdata_kind
{
	fk_new,
	fk_inc,
	fk_compare,
	fk_index,
	fk_free,
	
	fk_lambda_new,
	fk_lambda_evaluate,
	fk_lambda_free,
};

#endif
