/*  CPSC 323 - Compilers & Languages
    Programming Assignment 1
    Group Memebers:
        Angel Cervantes
        Christopher Liwanag
        Shuo Wang
    Problem Statement:
        Write a program to build a lexical analyzer. The lexical analyzer should accept a .txt file as an
        input, consisting of code snippets and comments, and it gives output by tokenizing the input file.
    Due:
        November 10, 2023
*/

#include "lex_analyzer.h"

// identify your input file directory here
#define INPUT_FILE_PATH "/Users/quis/Documents/cpsc323_f23_src/"
// identify your input file name including extension here
#define INPUT_FILE_NAME "input.txt"

int main()
{
    LexAnalyzer lexA{};

    lexA.analyze(INPUT_FILE_PATH, INPUT_FILE_PATH);

    return 0;
}
