Naming conventions:

All names shell have english roots, no any other language is permitted
(including spanish, russian, german etc.)

Any custom data type (struct, class):
* Use upper case letters as word separators, lower case for the rest of a word
* Always use "I" prefix for pure or partially virtual classes and structures
* No underscore ('_') symbol shell be used
* First character in a name must be upper case
* In the case that a word is an abbreviation - all abbreviation letters is an upper case
Examples: MyClassName, MyStructName

Type aliases:
* Always use first letter 't'
* Use a custom data type rules for the rest
* Use a tPtr prefix if this an alias to a pointer type
Example: using tPtrMyClassName = std::shared_ptr<MyClassName>;

Enumerations:
* Always use the enum class, not an old plain enum
* In enum name all letters are upper case
* In enum values all letters are upper case
* A word separator is an underscore symbol ('_')
Example: enum class MY_ENUM_TYPE{VAL_1, VAL_2};

Functions and variables:
* All letters are lower case
* A word separator is an underscore symbol ('_')
Examples: my_function, my_local_or_global_variable

Comments of type //:
* used for one sentence comments only
* start from space
* no capital letters at the beginngng
* no point at the end
Example: // my comment

Comments of type /**/:
* use capitals and points as in the regular text

Special aliases are (keep these names the same for all nodes):
tIn
tOut
tPtrIn
tPtrOut
tBase
tPtrNext

CONVENTIONS
1. Never use namespaces in *.h
2. Pure headers that does not contain templates are *.h
3. Headers that contain template implementations are *.hpp