#include "arith_lib.h"

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>

#define MAX_DEPTH 64
#define MAX_STEPS 32

static struct arith_step steps[MAX_STEPS];
static size_t nsteps;

static void skip_spaces(const char **s) {
    while (isspace((unsigned char)**s)) ++*s;
}

static int is_int(double x, double limit) {
    return x == floor(x) && fabs(x) <= limit;
}

static long long ipow(long long base, int n) {
    long long r = 1;
    while (n-- > 0) r *= base;
    return r;
}

/* expression := number | '(' expression operator expression ')' */
static int parse(const char **s, double *result, int depth) {
    if (depth > MAX_DEPTH) return 0;
    skip_spaces(s);

    if (**s != '(') {
        char *end;
        errno = 0;
        double x = strtod(*s, &end);
        if (end == *s || errno == ERANGE || !isfinite(x)) return 0;
        *s = end;
        *result = x;
        return 1;
    }

    ++*s;  /* opening '(' */
    double left, right;
    if (!parse(s, &left, depth + 1)) return 0;

    skip_spaces(s);
    char op = **s;
    if (op != '+' && op != '-' && op != '*' && op != '/' && op != '^')
        return 0;
    ++*s;

    if (!parse(s, &right, depth + 1)) return 0;
    skip_spaces(s);
    if (**s != ')') return 0;
    ++*s;

    switch (op) {
        case '+': *result = left + right; break;
        case '-': *result = left - right; break;
        case '*': *result = left * right; break;
        case '/':
            if (right == 0.0) return 0;
            *result = left / right;
            break;
        case '^':
            /* pow() is slow, and small integer powers are the common case. */
            if (is_int(left, 1e9) && is_int(right, 64) && right >= 0) {
                *result = (double)ipow((long long)left, (int)right);
                break;
            }
            errno = 0;
            *result = pow(left, right);
            if (errno != 0) return 0;
            break;
    }

    steps[nsteps++] = (struct arith_step){ op, left, right, *result };
    return isfinite(*result);
}

int arith_eval(const char *expr, double *result, const char **end) {
    const char *s = expr;
    nsteps = 0;
    int ok = parse(&s, result, 0);
    skip_spaces(&s);
    *end = s;
    if (!ok) return ARITH_ERR_INVALID;
    if (*s != '\0') return ARITH_ERR_TRAILING;
    return ARITH_OK;
}

size_t arith_trace(const struct arith_step **out) {
    *out = steps;
    return nsteps;
}
