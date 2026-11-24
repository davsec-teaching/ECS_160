# ECS160-HW4

## Due date: 12/11/2026 (last day of the quarter)
Note: no late days will be permitted on this homework

## Problem: Using AFL++ for fuzzing an arithmetic expression evaluator

## Points: 8 points

_Learning objectives:_

1. Compiling an application with the Fuzzer instrumentation.
2. Writing a fuzzing dictionary for an input language.
3. Compiling the application with the Sanitizer + Fuzzer instrumentation.
4. Writing a grammar-aware custom mutator.

_Necessary background knowledge:_

1. Fuzzers
2. Sanitizers
3. Grammars and parsers (flex and yacc)

_Problem Statement:_
We learned about fuzzers and sanitizers in class. In this homework, we will evaluate the effectiveness of three fuzzing strategies on `arith`, a small evaluator for arithmetic expressions.
We will first perform naive fuzzing with a dictionary,
then fuzzing with a dictionary and sanitizers, and finally, fuzzing with a grammar-aware custom mutator.

### The `arith` application

The source code of `arith` is provided in this directory:

- `arith_lib.c`, `arith_lib.h`: the arithmetic parser and evaluator (`arith_eval`).
- `main.c`: reads one expression from `stdin`, evaluates it, and prints the result.
- `Makefile`: builds the `arith` binary. It uses `$(CC)` and `$(CFLAGS)`, so you can override the compiler and the flags on the `make` command line. It is recommended that you use `gcc` as the compiler, though `clang` would also likely work.

`arith` accepts expressions in the following grammar:

```
expression := number | '(' expression operator expression ')'
operator   := '+' | '-' | '*' | '/' | '^'
```

Sample usage:

```bash
$ make
$ echo '((3*4)-(10/4))' | ./arith
9.5
```

Because `arith` reads its input from `stdin`, you do not need to write a test harness for this homework. AFL++ can pass each test case to the program on its standard input (leave `@@` off the `afl-fuzz` command line).

### Submission instructions

Please submit the following items on Gradescope. We won't have an autograder and we will grade each homework manually.

1. Your seed inputs and your dictionary file (Part A).
2. A script to automate the generation of the fuzzing targets. The script should:
   1) clone and build AFL++.
   2) compile `arith` with each of the configurations described in Part A, B, and C.
   3) build your custom mutator (Part C).
3. The source code of your custom mutator (Part C).
4. An `ANALYSIS.md` file that describes the results of the experiments described in Part A, B, and C, and compares the three configurations.

Please aswer the following questions:

   1) The machine specs you ran your experiment on (CPU, memory, etc)
   2) Which configuration (A/B/C) reached the most coverage, and why? You _can_ run each configuration on a different machine - in that case, describe the specs of each machine for each configuration. Running all three on the same machine makes the numbers easier to compare.
   3) Which configuration reached the highest throughput and why?
   4) How many bugs did each configuration find? Describe them. Could you manually verify any of the bugs? If no, why not?

### Part A: Running the application with the AFL++ fuzzer and a dictionary

1. First, compile AFL++ according to the instructions [here](https://github.com/AFLplusplus/AFLplusplus/blob/stable/docs/INSTALL.md).
2. Compile `arith` with the `afl-cc` compiler generated in the previous step.
3. Create a directory with at least 5 seed inputs. Each seed should be a valid `arith` expression. Use the same seeds in Part A, B, and C.
4. Create an AFL++ dictionary for the `arith` input language. Check [here](https://github.com/AFLplusplus/AFLplusplus/blob/stable/dictionaries/README.md) for the dictionary format. Think about which tokens the parser in `arith_lib.c` and `strtod()` look for.
5. Fuzz the generated binary for 30 minutes **with your seeds and your dictionary** (`-x`).
   1) Report the number of crashes found, the coverage, and the execution throughput.

### Part B: Running the application with the AFL++ fuzzer, the dictionary, and the ASAN and UBSAN sanitizers enabled

1. Recompile `arith` with the ASAN and UBSAN sanitizers.
2. Fuzz the generated binary for 30 minutes with the seeds and the dictionary from Part A.
3. Report the number of crashes found, the coverage, and the execution throughput. How does the throughput compare to Part A, and why?

### Part C: Write a grammar-aware custom mutator for `arith`

AFL++ allows the user to write custom mutators for the fuzzing target being fuzzed. This allows the user to add custom mutation logic specific to the target being fuzzed. Check [here](https://aflplus.plus/docs/custom_mutators/) for the documentation.

A suggested design for your grammar-aware mutator could involve generating the Abstract Syntax Tree (AST) using `flex` and `yacc`. Alternately, you could also
use regular expressions or any other simpler approach. Either way, you should:

1. Develop a grammar-aware custom mutator for `arith`. Note that the mutator itself can be in any language. Implement at least `afl_custom_init`, `afl_custom_fuzz` and `afl_custom_deinit`, and build the mutator as a shared library.
2. Fuzz the binary generated in Part B with the custom mutator for 30 minutes, with the seeds from Part A. AFL++ loads the mutator from the `AFL_CUSTOM_MUTATOR_LIBRARY` environment variable. By default, AFL++ also runs its own byte-level mutations alongside your mutator, and `AFL_CUSTOM_MUTATOR_ONLY=1` runs only your mutator. In the ANALYSIS.md report, state which one you used.
3. Report the number of crashes found, the coverage, and the execution throughput.
4. Also, describe your mutation logic.

### Notes

Do not put the AFL++ output directory in a cloud-synced folder (Google Drive, Dropbox, etc). AFL++ writes to it thousands of times per second and it will slowdown your fuzzer throughput.

### Grading Rubric

1. Part A: 2 points
2. Part B: 3 points
3. Part C: 3 points