# Naming Conventions
Here are the various rules used for naming in this codebase. These are followed
at all times for C++ code; possible exceptions being maybe code generated by
macros.

## Variables and functions
CamelCase (e.g. printText(), int someNum). Private member variables will have
a single underscore as a suffix.

## Types - Classes, structs and typedefs
PascalCase (e.g. class FileStream).

## Namespaces
All lowercase. If you can't fit a namespace name into one word, it shouldn't
be a single namespace!

## Macros
All-caps snake-case (e.g. SOME_MACRO). Library internal usage macros will be
suffixed with a single underscore.

## Files and Directories
All lowercase with hyphens as delimitation (e.g. io-writer.hpp). C++ code will
have file types .cpp and .hpp.

## Template parameters
PascalCase (e.g. typename T, typename BasicType).
