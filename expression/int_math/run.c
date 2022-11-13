
#include <assert.h>
#include <gmp.h>

#include <debug.h>

#include <value/int/struct.h>
#include <value/int/new.h>

#include <mpz/struct.h>
#include <mpz/new.h>
#include <mpz/free.h>

#include "run.h"

struct value* int_math_add_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	mpz_add(mpz->mpz, left->value->mpz, right->value->mpz);
	
	struct value* value = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}

struct value* int_math_sub_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	mpz_sub(mpz->mpz, left->value->mpz, right->value->mpz);
	
	struct value* value = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}

struct value* int_math_mult_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	mpz_mul(mpz->mpz, left->value->mpz, right->value->mpz);
	
	struct value* value = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}

struct value* int_math_qdiv_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	mpz_fdiv_q(mpz->mpz, left->value->mpz, right->value->mpz);
	
	struct value* value = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}

struct value* int_math_rdiv_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	mpz_fdiv_r(mpz->mpz, left->value->mpz, right->value->mpz);
	
	struct value* value = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}

struct value* int_math_lshift_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	if (mpz_cmp_ui(right->value->mpz, 0) < 0)
	{
		if (mpz_fits_slong_p(right->value->mpz))
		{
			signed long right_slong = mpz_get_si(right->value->mpz);
			
			mpz_fdiv_q_2exp(mpz->mpz, left->value->mpz, -right_slong);
		}
		else
		{
			TODO;
		}
	}
	else if (mpz_fits_ulong_p(right->value->mpz))
	{
		unsigned long right_ulong = mpz_get_ui(right->value->mpz);
		
		mpz_mul_2exp(mpz->mpz, left->value->mpz, right_ulong);
	}
	else
	{
		TODO;
	}
	
	struct value* value = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}

struct value* int_math_rshift_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	if (mpz_cmp_ui(right->value->mpz, 0) < 0)
	{
		if (mpz_fits_slong_p(right->value->mpz))
		{
			signed long right_slong = mpz_get_si(right->value->mpz);
			
			mpz_mul_2exp(mpz->mpz, left->value->mpz, -right_slong);
		}
		else
		{
			TODO;
		}
	}
	else if (mpz_fits_ulong_p(right->value->mpz))
	{
		unsigned long right_ulong = mpz_get_ui(right->value->mpz);
		
		mpz_fdiv_q_2exp(mpz->mpz, left->value->mpz, right_ulong);
	}
	else
	{
		TODO;
	}
	
	struct value* value = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}

struct value* int_math_expo_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	if (mpz_fits_ulong_p(right->value->mpz))
	{
		unsigned long right_ulong = mpz_get_ui(right->value->mpz);
		
		mpz_pow_ui(mpz->mpz, left->value->mpz, right_ulong);
	}
	else if (mpz_cmp_ui(right->value->mpz, 0) < 0)
	{
		TODO;
	}
	else
	{
		TODO;
	}
	
	struct value* value = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}

struct value* int_math_bitand_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	mpz_and(mpz->mpz, left->value->mpz, right->value->mpz);
	
	struct value* value = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}

struct value* int_math_bitor_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	mpz_ior(mpz->mpz, left->value->mpz, right->value->mpz);
	
	struct value* value = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}

struct value* int_math_bitxor_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	mpz_xor(mpz->mpz, left->value->mpz, right->value->mpz);
	
	struct value* value = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}

struct value* int_math_negate_run(
	struct type* type,
	struct int_value* left)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	mpz_neg(mpz->mpz, left->value->mpz);
	
	struct value* value = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}


struct value* int_math_bitnegate_run(
	struct type* type,
	struct int_value* left)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	mpz_com(mpz->mpz, left->value->mpz);
	
	struct value* value = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}
























