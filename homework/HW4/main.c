#include "arith_lib.h"

#include <stdio.h>
#include <stdlib.h>

static void print_trace(void) {
    const struct arith_step *steps;
    size_t count = arith_trace(&steps);
    for (size_t i = 0; i < count; i++)
        fprintf(stderr, "(%.12g %c %.12g) = %.12g\n",
                steps[i].left, steps[i].op, steps[i].right, steps[i].result);
}

/* Show the unexpected text up to the end of its line. */
static void report_trailing(const char *end) {
    char extra[32];
    size_t i = 0;
    while (end[i] != '\0' && end[i] != '\n') {
        extra[i] = end[i];
        i++;
    }
    extra[i] = '\0';
    fprintf(stderr, "Unexpected characters after expression: '%s'\n", extra);
}

int main(void) {
    char input[4096];
    size_t n = fread(input, 1, sizeof(input), stdin);
    input[n] = '\0';

    double result;
    const char *end;
    switch (arith_eval(input, &result, &end)) {
        case ARITH_OK:
            if (getenv("ARITH_TRACE")) print_trace();
            printf("%.12g\n", result);
            return 0;
        case ARITH_ERR_TRAILING:
            report_trailing(end);
            return 1;
        default:
            fprintf(stderr, "Invalid expression or arithmetic error\n");
            return 1;
    }
}
