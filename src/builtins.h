#ifndef TLISP_BUILTINS_H_
#define TLISP_BUILTINS_H_

#include "core.h"

typedef struct env_t env_t; // Forward declaration.

tlisp_obj_t *tlisp_nil;
tlisp_obj_t *tlisp_true;
tlisp_obj_t *tlisp_false;

tlisp_obj_t *tlisp_add(tlisp_obj_t *args, env_t *);
tlisp_obj_t *tlisp_sub(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_mul(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_div(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_arith_and(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_arith_or(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_xor(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_equals(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_greater_than(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_less_than(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_geq(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_leq(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_and(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_or(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_not(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_def(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_set(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_cons(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_car(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_cdr(tlisp_obj_t *, env_t *);
tlisp_obj_t *tlisp_print(tlisp_obj_t *, env_t *);

#endif