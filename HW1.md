# Design Patterns (Total Points: 5 (5% of grade), Due Date: Oct 9, 11:59 PM)

Clone the repository from the [HW1 handout repository](https://github.com/davsec-teaching/F26-HW1-handout). If you choose to fork it, make sure you mark the fork as **private**.

The assignment consists of three parts. For each part, some existing code, including test cases are provided. Please do not modify them or the build scripts. Fill free to _add_ content and create your own files.
Every sub-part has its own `main` function, which contains assertions that you can check your solution against. You can use `./grade.sh` to test your solution.

All submissions must be done on Gradescope.

## Part A

Design a `Configuration` class, which contains fields for `appName`, `logLevel`, `maxConnections`, and `debugMode`. The default values for these fields are `ECS160-HW1`, `INFO`, `32`, and `true`. You must, however, ensure that there is a single instance of the `Configuration` class in the application and that the instance
is accessible from anywhere in the application. You must implement this design in Java (0.5 points), C++ (1 point), and Python (1 point).

The following hints might help. For C++,

- For every class, a [copy constructor](https://en.cppreference.com/cpp/language/copy_constructor) is implicitly created. Does this complicate your design? If so, how would you handle it?
- For every class, a [copy assignment operator](https://en.cppreference.com/cpp/language/copy_assignment) is implicitly created. Does this complicate your design? If so, how would you handle it?

For Python,

- Python supports [name mangling](https://realpython.com/ref/glossary/name-mangling/).

## Part B

The handout provides a `User` interface with the methods `getName`, `getEmail`, and `setEmail`, and an `AdminUser` class that implements it.
Add logging to `AdminUser` such that every call to a `User` method must print a line of the form `[LOG] AdminUser.setEmail("alice@ucdavis.edu")` before running the method.
For the Java version, you must not modify `AdminUser`, and code that already uses a `User` must work unchanged with a logged one. You must implement this design in Java (0.5 point) and Python (1 point).

For Python,

- Python has built-in syntax for [decorators](https://realpython.com/primer-on-python-decorators/) (`@log`). You must use it.
- [`functools.wraps`](https://docs.python.org/3/library/functools.html#functools.wraps) keeps a wrapped method's name, which you need to print the log line.
- Is there any disadvantage to using Python's decorator annotation over implementing the pattern yourself? Write your answer in a `Solution.md` file.

## Part C

Compilers and interpreters commonly represent programs as an Abstract Syntax Tree (AST). For example, `10 + (2 * 3)` can be represented as:

        +
       / \
     10   *
         / \
        2   3

Many operations, such as evaluation, type checking, and printing, may need to run over the same AST.

Your goal is to implement an "evaluator" for this AST. Adding a new operation later must not require changing any of the node classes. You can assume that all nodes are integers.
Make sure that your design can detect at compile time, when a new operation is defined, but not handled. For example, imagine you add a new "modulo" operation, but your evaluator does
not handle it yet. In that case, the compiler should throw an error.

First implement this design in Java (1 point).

### Extra credit: Rust (1 point)

Implement the same evaluator in Rust. Instead of trying to replicate the Java design in Rust, first check whether Rust has a language feature that gives you most
of what the design pattern provides. Your solution should still guarantee that when a new node type is added, the compiler points out every operation that doesn't handle it yet.

If you do not know Rust but still want to attempt this homework, you can quickly skim through chapters 1-6 from the [Rust book](https://doc.rust-lang.org/book/), with
more emphasis on Chapter 6.
