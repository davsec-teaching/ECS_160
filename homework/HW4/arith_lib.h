#ifndef ARITH_LIB_H
#define ARITH_LIB_H

#include <stddef.h>

/* Return codes of arith_eval. */
enum {
    ARITH_OK = 0,
    ARITH_ERR_INVALID,   /* malformed expression or arithmetic error */
    ARITH_ERR_TRAILING   /* valid expression followed by extra characters */
};

/* One binary operation performed while evaluating an expression. */
struct arith_step {
    char op;
    double left, right, result;
};

/*
 * Evaluates a NUL-terminated expression:
 *
 *   expression := number | '(' expression operator expression ')'
 *   operator   := '+' | '-' | '*' | '/' | '^'
 *
 * On ARITH_OK, stores the value in *result. On ARITH_ERR_TRAILING, *end
 * points to the first unexpected character.
 */
int arith_eval(const char *expr, double *result, const char **end);

/* The operations performed by the last call to arith_eval, in order. */
size_t arith_trace(const struct arith_step **steps);

#endif
